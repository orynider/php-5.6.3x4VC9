#include "cpluscommon.h"
#include "gtk.h"
#include <lber.h>
#include <ldap.h>
#include <My_Window.h>
#include <Gtk_LdapItem.h>
#include <Gtk_LdapServer.h>

int debug_level = 0;

target_drag_leave(GdkDragContext *context, guint time) {
}

int main(int argc, char **argv) {
	My_Window *window;
	Gtk_LdapItem *treeresult;
	Gtk_Tree *tree = NULL, *subtree = NULL;
	Gtk_Tree *machine, *machinetree;
	Gtk_LdapServer *server;
	Gtk_Viewport *viewport;
	char *host = NULL, *prt = NULL;
	char *base_dn = NULL;
	int c, port = 0;
	GList *hosts = NULL;
	int host_count = 0;
	char *pair[2];

	//hosts = new G_List<char>();
	while ((c = getopt(argc, argv, "d:s:p:h")) != -1) {
		switch (c) {
			case 'd':
				debug_level = atoi(optarg);
				break;
			case 's':
				debug("host\n");
				hosts = g_list_append(hosts, (strdup(optarg)));
				break;
			case 'p':
				port = atoi(optarg); break;
			case 'h':
	                default:
				fprintf(stderr, "Usage: %s [-d level] [-s server[:port]]*\n", argv[0]);
				exit(-1);
		}
		fprintf(stderr,"b");
	}
	debug("%i hosts\n", g_list_length(hosts));
	if (g_list_length(hosts) == 0) {
#ifndef LDAP_GET_OPT
		ldap_get_option(NULL, LDAP_OPT_HOST_NAME, host);
#endif /* LDAP_GET_OPT */
		if (host!=NULL) {
			hosts = g_list_append(hosts, host);
			debug("Default host: %s\n", host);
		} else {
#ifndef LDAP_GET_OPT
			fprintf(stderr,"Why isn't your LDAP_OPT_HOST_NAME defined?\n");
#endif
			fprintf(stderr,"Supply me with a host please (hint: use -s)\n");
		}
	} else {	
		for (int f=0; f<g_list_length(hosts); f++) {
			debug("%s\n", g_list_nth(hosts,f)->data);
		}
	}
	if (port == 0) port = LDAP_PORT;

	Gtk_Main m(&argc, &argv);

	window = new My_Window(GTK_WINDOW_TOPLEVEL);

	if (hosts!=NULL) {
		tree = new Gtk_Tree();
		window->viewport->add(*tree);
		for (int f=0; f<g_list_length(hosts); f++) {
			host = strtok((char*)g_list_nth(hosts, f)->data, ":");
			prt = strtok(NULL, "\0");
			if (prt != NULL) port = atoi(prt);
			else port = LDAP_PORT;
			server = new Gtk_LdapServer(window, host, port);
			subtree = server->getSubtree();
			tree->append(*server);
			server->set_subtree(*subtree);
			server->show();
		}
		//window->viewport->add(*tree);
//		tree->show();
	}

//	window->viewport->show();
//	window->scroller->show();

	//Select first server
	if (tree != NULL) {
		Gtk_LdapTree::ItemList &items = tree->tree();
		Gtk_LdapTree::ItemList::iterator i = items.begin();
		server = (Gtk_LdapServer *)(* i);
	//	server->select_impl();
	}

	window->set_title("gtk-tool");
	window->activate();
	window->set_usize(600, 500);

	window->set_events(window->get_events()|GDK_ALL_EVENTS_MASK);
	window->drag_dest_set(GTK_DEST_DEFAULT_ALL, target_table, n_targets, static_cast <GdkDragAction> (GDK_ACTION_COPY|GDK_ACTION_MOVE));
	window->drag_source_set(static_cast<GdkModifierType>(GDK_BUTTON1_MASK|GDK_BUTTON3_MASK), target_table, n_targets, static_cast<GdkDragAction>(GDK_ACTION_COPY|GDK_ACTION_MOVE));
        window->drag_leave.connect(window->slot(window,target_drag_leave));
	window->show_all();

	m.run();
	return 0;
}
