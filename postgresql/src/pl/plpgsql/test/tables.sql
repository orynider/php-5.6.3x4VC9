-- ************************************************************
-- * 
-- * Tables for the patchfield test of PL/pgSQL
-- * 
-- * $Header: /cvsroot/pgsql-server/src/pl/plpgsql/test/Attic/tables.sql,v 1.1 1998/08/24 19:16:27 momjian Exp $
-- * 
-- ************************************************************

create table Room (
    roomno	char(8),
    comment	text
);

create unique index Room_rno on Room using btree (roomno bpchar_ops);


create table WSlot (
    slotname	char(20),
    roomno	char(8),
    slotlink	char(20),
    backlink	char(20)
);

create unique index WSlot_name on WSlot using btree (slotname bpchar_ops);


create table PField (
    name	text,
    comment	text
);

create unique index PField_name on PField using btree (name text_ops);


create table PSlot (
    slotname	char(20),
    pfname	text,
    slotlink	char(20),
    backlink	char(20)
);

create unique index PSlot_name on PSlot using btree (slotname bpchar_ops);


create table PLine (
    slotname	char(20),
    phonenumber	char(20),
    comment	text,
    backlink	char(20)
);

create unique index PLine_name on PLine using btree (slotname bpchar_ops);


create table Hub (
    name	char(14),
    comment	text,
    nslots	integer
);

create unique index Hub_name on Hub using btree (name bpchar_ops);


create table HSlot (
    slotname	char(20),
    hubname	char(14),
    slotno	integer,
    slotlink	char(20)
);

create unique index HSlot_name on HSlot using btree (slotname bpchar_ops);
create index HSlot_hubname on HSlot using btree (hubname bpchar_ops);


create table System (
    name	text,
    comment	text
);

create unique index System_name on System using btree (name text_ops);


create table IFace (
    slotname	char(20),
    sysname	text,
    ifname	text,
    slotlink	char(20)
);

create unique index IFace_name on IFace using btree (slotname bpchar_ops);


create table PHone (
    slotname	char(20),
    comment	text,
    slotlink	char(20)
);

create unique index PHone_name on PHone using btree (slotname bpchar_ops);


