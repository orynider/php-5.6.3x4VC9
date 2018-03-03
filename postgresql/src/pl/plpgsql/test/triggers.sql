-- ************************************************************
-- * 
-- * Trigger procedures and functions for the patchfield
-- * test of PL/pgSQL
-- * 
-- * $Header: /cvsroot/pgsql-server/src/pl/plpgsql/test/Attic/triggers.sql,v 1.2 2000/10/22 23:25:11 tgl Exp $
-- * 
-- ************************************************************


-- ************************************************************
-- * AFTER UPDATE on Room
-- *	- If room no changes let wall slots follow
-- ************************************************************
create function tg_room_au() returns opaque as '
begin
    if new.roomno != old.roomno then
        update WSlot set roomno = new.roomno where roomno = old.roomno;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_room_au after update
    on Room for each row execute procedure tg_room_au();


-- ************************************************************
-- * AFTER DELETE on Room
-- *	- delete wall slots in this room
-- ************************************************************
create function tg_room_ad() returns opaque as '
begin
    delete from WSlot where roomno = old.roomno;
    return old;
end;
' language 'plpgsql';

create trigger tg_room_ad after delete
    on Room for each row execute procedure tg_room_ad();


-- ************************************************************
-- * BEFORE INSERT or UPDATE on WSlot
-- *	- Check that room exists
-- ************************************************************
create function tg_wslot_biu() returns opaque as '
begin
    if count(*) = 0 from Room where roomno = new.roomno then
        raise exception ''Room % does not exist'', new.roomno;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_wslot_biu before insert or update
    on WSlot for each row execute procedure tg_wslot_biu();


-- ************************************************************
-- * AFTER UPDATE on PField
-- *	- Let PSlots of this field follow
-- ************************************************************
create function tg_pfield_au() returns opaque as '
begin
    if new.name != old.name then
        update PSlot set pfname = new.name where pfname = old.name;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_pfield_au after update
    on PField for each row execute procedure tg_pfield_au();


-- ************************************************************
-- * AFTER DELETE on PField
-- *	- Remove all slots of this patchfield
-- ************************************************************
create function tg_pfield_ad() returns opaque as '
begin
    delete from PSlot where pfname = old.name;
    return old;
end;
' language 'plpgsql';

create trigger tg_pfield_ad after delete
    on PField for each row execute procedure tg_pfield_ad();


-- ************************************************************
-- * BEFORE INSERT or UPDATE on PSlot
-- *	- Ensure that our patchfield does exist
-- ************************************************************
create function tg_pslot_biu() returns opaque as '
declare
    pfrec	record;
    rename new to ps;
begin
    select into pfrec * from PField where name = ps.pfname;
    if not found then
        raise exception ''Patchfield "%" does not exist'', ps.pfname;
    end if;
    return ps;
end;
' language 'plpgsql';

create trigger tg_pslot_biu before insert or update
    on PSlot for each row execute procedure tg_pslot_biu();


-- ************************************************************
-- * AFTER UPDATE on System
-- *	- If system name changes let interfaces follow
-- ************************************************************
create function tg_system_au() returns opaque as '
begin
    if new.name != old.name then
        update IFace set sysname = new.name where sysname = old.name;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_system_au after update
    on System for each row execute procedure tg_system_au();


-- ************************************************************
-- * BEFORE INSERT or UPDATE on IFace
-- *	- set the slotname to IF.sysname.ifname
-- ************************************************************
create function tg_iface_biu() returns opaque as '
declare
    sname	text;
    sysrec	record;
begin
    select into sysrec * from system where name = new.sysname;
    if not found then
        raise exception ''system "%" does not exist'', new.sysname;
    end if;
    sname := ''IF.'' || new.sysname;
    sname := sname || ''.'';
    sname := sname || new.ifname;
    if length(sname) > 20 then
        raise exception ''IFace slotname "%" too long (20 char max)'', sname;
    end if;
    new.slotname := sname;
    return new;
end;
' language 'plpgsql';

create trigger tg_iface_biu before insert or update
    on IFace for each row execute procedure tg_iface_biu();


-- ************************************************************
-- * AFTER INSERT or UPDATE or DELETE on Hub
-- *	- insert/delete/rename slots as required
-- ************************************************************
create function tg_hub_a() returns opaque as '
declare
    hname	text;
    dummy	integer;
begin
    if tg_op = ''INSERT'' then
	dummy := tg_hub_adjustslots(new.name, 0, new.nslots);
	return new;
    end if;
    if tg_op = ''UPDATE'' then
	if new.name != old.name then
	    update HSlot set hubname = new.name where hubname = old.name;
	end if;
	dummy := tg_hub_adjustslots(new.name, old.nslots, new.nslots);
	return new;
    end if;
    if tg_op = ''DELETE'' then
	dummy := tg_hub_adjustslots(old.name, old.nslots, 0);
	return old;
    end if;
end;
' language 'plpgsql';

create trigger tg_hub_a after insert or update or delete
    on Hub for each row execute procedure tg_hub_a();


-- ************************************************************
-- * Support function to add/remove slots of Hub
-- ************************************************************
create function tg_hub_adjustslots(bpchar, integer, integer)
returns integer as '
declare
    hname	alias for $1;
    oldnslots	alias for $2;
    newnslots	alias for $3;
begin
    if newnslots = oldnslots then
        return 0;
    end if;
    if newnslots < oldnslots then
        delete from HSlot where hubname = hname and slotno > newnslots;
	return 0;
    end if;
    for i in oldnslots + 1 .. newnslots loop
        insert into HSlot (slotname, hubname, slotno, slotlink)
		values (''HS.dummy'', hname, i, '''');
    end loop;
    return 0;
end;
' language 'plpgsql';


-- ************************************************************
-- * BEFORE INSERT or UPDATE on HSlot
-- *	- prevent from manual manipulation
-- *	- set the slotname to HS.hubname.slotno
-- ************************************************************
create function tg_hslot_biu() returns opaque as '
declare
    sname	text;
    xname	HSlot.slotname%TYPE;
    hubrec	record;
begin
    select into hubrec * from Hub where name = new.hubname;
    if not found then
        raise exception ''no manual manipulation of HSlot'';
    end if;
    if new.slotno < 1 or new.slotno > hubrec.nslots then
        raise exception ''no manual manipulation of HSlot'';
    end if;
    if tg_op = ''UPDATE'' then
	if new.hubname != old.hubname then
	    if count(*) > 0 from Hub where name = old.hubname then
		raise exception ''no manual manipulation of HSlot'';
	    end if;
	end if;
    end if;
    sname := ''HS.'' || trim(new.hubname);
    sname := sname || ''.'';
    sname := sname || new.slotno::text;
    if length(sname) > 20 then
        raise exception ''HSlot slotname "%" too long (20 char max)'', sname;
    end if;
    new.slotname := sname;
    return new;
end;
' language 'plpgsql';

create trigger tg_hslot_biu before insert or update
    on HSlot for each row execute procedure tg_hslot_biu();


-- ************************************************************
-- * BEFORE DELETE on HSlot
-- *	- prevent from manual manipulation
-- ************************************************************
create function tg_hslot_bd() returns opaque as '
declare
    hubrec	record;
begin
    select into hubrec * from Hub where name = old.hubname;
    if not found then
        return old;
    end if;
    if old.slotno > hubrec.nslots then
        return old;
    end if;
    raise exception ''no manual manipulation of HSlot'';
end;
' language 'plpgsql';

create trigger tg_hslot_bd before delete
    on HSlot for each row execute procedure tg_hslot_bd();


-- ************************************************************
-- * BEFORE INSERT on all slots
-- *	- Check name prefix
-- ************************************************************
create function tg_chkslotname() returns opaque as '
begin
    if substr(new.slotname, 1, 2) != tg_argv[0] then
        raise exception ''slotname must begin with %'', tg_argv[0];
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_chkslotname before insert
    on PSlot for each row execute procedure tg_chkslotname('PS');

create trigger tg_chkslotname before insert
    on WSlot for each row execute procedure tg_chkslotname('WS');

create trigger tg_chkslotname before insert
    on PLine for each row execute procedure tg_chkslotname('PL');

create trigger tg_chkslotname before insert
    on IFace for each row execute procedure tg_chkslotname('IF');

create trigger tg_chkslotname before insert
    on PHone for each row execute procedure tg_chkslotname('PH');


-- ************************************************************
-- * BEFORE INSERT or UPDATE on all slots with slotlink
-- *	- Set slotlink to empty string if NULL value given
-- ************************************************************
create function tg_chkslotlink() returns opaque as '
begin
    if new.slotlink isnull then
        new.slotlink := '''';
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_chkslotlink before insert or update
    on PSlot for each row execute procedure tg_chkslotlink();

create trigger tg_chkslotlink before insert or update
    on WSlot for each row execute procedure tg_chkslotlink();

create trigger tg_chkslotlink before insert or update
    on IFace for each row execute procedure tg_chkslotlink();

create trigger tg_chkslotlink before insert or update
    on HSlot for each row execute procedure tg_chkslotlink();

create trigger tg_chkslotlink before insert or update
    on PHone for each row execute procedure tg_chkslotlink();


-- ************************************************************
-- * BEFORE INSERT or UPDATE on all slots with backlink
-- *	- Set backlink to empty string if NULL value given
-- ************************************************************
create function tg_chkbacklink() returns opaque as '
begin
    if new.backlink isnull then
        new.backlink := '''';
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_chkbacklink before insert or update
    on PSlot for each row execute procedure tg_chkbacklink();

create trigger tg_chkbacklink before insert or update
    on WSlot for each row execute procedure tg_chkbacklink();

create trigger tg_chkbacklink before insert or update
    on PLine for each row execute procedure tg_chkbacklink();


-- ************************************************************
-- * BEFORE UPDATE on PSlot
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_pslot_bu() returns opaque as '
begin
    if new.slotname != old.slotname then
        delete from PSlot where slotname = old.slotname;
	insert into PSlot (
		    slotname,
		    pfname,
		    slotlink,
		    backlink
		) values (
		    new.slotname,
		    new.pfname,
		    new.slotlink,
		    new.backlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_pslot_bu before update
    on PSlot for each row execute procedure tg_pslot_bu();


-- ************************************************************
-- * BEFORE UPDATE on WSlot
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_wslot_bu() returns opaque as '
begin
    if new.slotname != old.slotname then
        delete from WSlot where slotname = old.slotname;
	insert into WSlot (
		    slotname,
		    roomno,
		    slotlink,
		    backlink
		) values (
		    new.slotname,
		    new.roomno,
		    new.slotlink,
		    new.backlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_wslot_bu before update
    on WSlot for each row execute procedure tg_Wslot_bu();


-- ************************************************************
-- * BEFORE UPDATE on PLine
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_pline_bu() returns opaque as '
begin
    if new.slotname != old.slotname then
        delete from PLine where slotname = old.slotname;
	insert into PLine (
		    slotname,
		    phonenumber,
		    comment,
		    backlink
		) values (
		    new.slotname,
		    new.phonenumber,
		    new.comment,
		    new.backlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_pline_bu before update
    on PLine for each row execute procedure tg_pline_bu();


-- ************************************************************
-- * BEFORE UPDATE on IFace
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_iface_bu() returns opaque as '
begin
    if new.slotname != old.slotname then
        delete from IFace where slotname = old.slotname;
	insert into IFace (
		    slotname,
		    sysname,
		    ifname,
		    slotlink
		) values (
		    new.slotname,
		    new.sysname,
		    new.ifname,
		    new.slotlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_iface_bu before update
    on IFace for each row execute procedure tg_iface_bu();


-- ************************************************************
-- * BEFORE UPDATE on HSlot
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_hslot_bu() returns opaque as '
begin
    if new.slotname != old.slotname or new.hubname != old.hubname then
        delete from HSlot where slotname = old.slotname;
	insert into HSlot (
		    slotname,
		    hubname,
		    slotno,
		    slotlink
		) values (
		    new.slotname,
		    new.hubname,
		    new.slotno,
		    new.slotlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_hslot_bu before update
    on HSlot for each row execute procedure tg_hslot_bu();


-- ************************************************************
-- * BEFORE UPDATE on PHone
-- *	- do delete/insert instead of update if name changes
-- ************************************************************
create function tg_phone_bu() returns opaque as '
begin
    if new.slotname != old.slotname then
        delete from PHone where slotname = old.slotname;
	insert into PHone (
		    slotname,
		    comment,
		    slotlink
		) values (
		    new.slotname,
		    new.comment,
		    new.slotlink
		);
        return null;
    end if;
    return new;
end;
' language 'plpgsql';

create trigger tg_phone_bu before update
    on PHone for each row execute procedure tg_phone_bu();


-- ************************************************************
-- * AFTER INSERT or UPDATE or DELETE on slot with backlink
-- *	- Ensure that the opponent correctly points back to us
-- ************************************************************
create function tg_backlink_a() returns opaque as '
declare
    dummy	integer;
begin
    if tg_op = ''INSERT'' then
        if new.backlink != '''' then
	    dummy := tg_backlink_set(new.backlink, new.slotname);
	end if;
	return new;
    end if;
    if tg_op = ''UPDATE'' then
        if new.backlink != old.backlink then
	    if old.backlink != '''' then
	        dummy := tg_backlink_unset(old.backlink, old.slotname);
	    end if;
	    if new.backlink != '''' then
	        dummy := tg_backlink_set(new.backlink, new.slotname);
	    end if;
	else
	    if new.slotname != old.slotname and new.backlink != '''' then
	        dummy := tg_slotlink_set(new.backlink, new.slotname);
	    end if;
	end if;
	return new;
    end if;
    if tg_op = ''DELETE'' then
        if old.backlink != '''' then
	    dummy := tg_backlink_unset(old.backlink, old.slotname);
	end if;
	return old;
    end if;
end;
' language 'plpgsql';


create trigger tg_backlink_a after insert or update or delete
    on PSlot for each row execute procedure tg_backlink_a('PS');

create trigger tg_backlink_a after insert or update or delete
    on WSlot for each row execute procedure tg_backlink_a('WS');

create trigger tg_backlink_a after insert or update or delete
    on PLine for each row execute procedure tg_backlink_a('PL');


-- ************************************************************
-- * Support function to set the opponents backlink field
-- * if it does not already point to the requested slot
-- ************************************************************
create function tg_backlink_set(bpchar, bpchar)
returns integer as '
declare
    myname	alias for $1;
    blname	alias for $2;
    mytype	char(2);
    link	char(4);
    rec		record;
begin
    mytype := substr(myname, 1, 2);
    link := mytype || substr(blname, 1, 2);
    if link = ''PLPL'' then
        raise exception 
		''backlink between two phone lines does not make sense'';
    end if;
    if link in (''PLWS'', ''WSPL'') then
        raise exception 
		''direct link of phone line to wall slot not permitted'';
    end if;
    if mytype = ''PS'' then
        select into rec * from PSlot where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.backlink != blname then
	    update PSlot set backlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''WS'' then
        select into rec * from WSlot where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.backlink != blname then
	    update WSlot set backlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''PL'' then
        select into rec * from PLine where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.backlink != blname then
	    update PLine set backlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    raise exception ''illegal backlink beginning with %'', mytype;
end;
' language 'plpgsql';


-- ************************************************************
-- * Support function to clear out the backlink field if
-- * it still points to specific slot
-- ************************************************************
create function tg_backlink_unset(bpchar, bpchar)
returns integer as '
declare
    myname	alias for $1;
    blname	alias for $2;
    mytype	char(2);
    rec		record;
begin
    mytype := substr(myname, 1, 2);
    if mytype = ''PS'' then
        select into rec * from PSlot where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.backlink = blname then
	    update PSlot set backlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''WS'' then
        select into rec * from WSlot where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.backlink = blname then
	    update WSlot set backlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''PL'' then
        select into rec * from PLine where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.backlink = blname then
	    update PLine set backlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
end;
' language 'plpgsql';


-- ************************************************************
-- * AFTER INSERT or UPDATE or DELETE on slot with slotlink
-- *	- Ensure that the opponent correctly points back to us
-- ************************************************************
create function tg_slotlink_a() returns opaque as '
declare
    dummy	integer;
begin
    if tg_op = ''INSERT'' then
        if new.slotlink != '''' then
	    dummy := tg_slotlink_set(new.slotlink, new.slotname);
	end if;
	return new;
    end if;
    if tg_op = ''UPDATE'' then
        if new.slotlink != old.slotlink then
	    if old.slotlink != '''' then
	        dummy := tg_slotlink_unset(old.slotlink, old.slotname);
	    end if;
	    if new.slotlink != '''' then
	        dummy := tg_slotlink_set(new.slotlink, new.slotname);
	    end if;
	else
	    if new.slotname != old.slotname and new.slotlink != '''' then
	        dummy := tg_slotlink_set(new.slotlink, new.slotname);
	    end if;
	end if;
	return new;
    end if;
    if tg_op = ''DELETE'' then
        if old.slotlink != '''' then
	    dummy := tg_slotlink_unset(old.slotlink, old.slotname);
	end if;
	return old;
    end if;
end;
' language 'plpgsql';


create trigger tg_slotlink_a after insert or update or delete
    on PSlot for each row execute procedure tg_slotlink_a('PS');

create trigger tg_slotlink_a after insert or update or delete
    on WSlot for each row execute procedure tg_slotlink_a('WS');

create trigger tg_slotlink_a after insert or update or delete
    on IFace for each row execute procedure tg_slotlink_a('IF');

create trigger tg_slotlink_a after insert or update or delete
    on HSlot for each row execute procedure tg_slotlink_a('HS');

create trigger tg_slotlink_a after insert or update or delete
    on PHone for each row execute procedure tg_slotlink_a('PH');


-- ************************************************************
-- * Support function to set the opponents slotlink field
-- * if it does not already point to the requested slot
-- ************************************************************
create function tg_slotlink_set(bpchar, bpchar)
returns integer as '
declare
    myname	alias for $1;
    blname	alias for $2;
    mytype	char(2);
    link	char(4);
    rec		record;
begin
    mytype := substr(myname, 1, 2);
    link := mytype || substr(blname, 1, 2);
    if link = ''PHPH'' then
        raise exception 
		''slotlink between two phones does not make sense'';
    end if;
    if link in (''PHHS'', ''HSPH'') then
        raise exception 
		''link of phone to hub does not make sense'';
    end if;
    if link in (''PHIF'', ''IFPH'') then
        raise exception 
		''link of phone to hub does not make sense'';
    end if;
    if link in (''PSWS'', ''WSPS'') then
        raise exception 
		''slotlink from patchslot to wallslot not permitted'';
    end if;
    if mytype = ''PS'' then
        select into rec * from PSlot where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.slotlink != blname then
	    update PSlot set slotlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''WS'' then
        select into rec * from WSlot where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.slotlink != blname then
	    update WSlot set slotlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''IF'' then
        select into rec * from IFace where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.slotlink != blname then
	    update IFace set slotlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''HS'' then
        select into rec * from HSlot where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.slotlink != blname then
	    update HSlot set slotlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''PH'' then
        select into rec * from PHone where slotname = myname;
	if not found then
	    raise exception ''% does not exist'', myname;
	end if;
	if rec.slotlink != blname then
	    update PHone set slotlink = blname where slotname = myname;
	end if;
	return 0;
    end if;
    raise exception ''illegal slotlink beginning with %'', mytype;
end;
' language 'plpgsql';


-- ************************************************************
-- * Support function to clear out the slotlink field if
-- * it still points to specific slot
-- ************************************************************
create function tg_slotlink_unset(bpchar, bpchar)
returns integer as '
declare
    myname	alias for $1;
    blname	alias for $2;
    mytype	char(2);
    rec		record;
begin
    mytype := substr(myname, 1, 2);
    if mytype = ''PS'' then
        select into rec * from PSlot where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.slotlink = blname then
	    update PSlot set slotlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''WS'' then
        select into rec * from WSlot where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.slotlink = blname then
	    update WSlot set slotlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''IF'' then
        select into rec * from IFace where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.slotlink = blname then
	    update IFace set slotlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''HS'' then
        select into rec * from HSlot where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.slotlink = blname then
	    update HSlot set slotlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
    if mytype = ''PH'' then
        select into rec * from PHone where slotname = myname;
	if not found then
	    return 0;
	end if;
	if rec.slotlink = blname then
	    update PHone set slotlink = '''' where slotname = myname;
	end if;
	return 0;
    end if;
end;
' language 'plpgsql';


