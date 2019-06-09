# include <gtk/gtk.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <getopt.h>

GtkWidget *window, *image, *button, *hbox, *vbox, *hbox1, *yes_button, *no_button; 
int opt, t = 3000, yesno;
char msg[128] = "\n ", img[40] = "/usr/share/pixmaps/", *start;
	
static void usage(void) {
	
	printf("Notification GPL2 DdShurick\n\tVersion 0.0b\n");
	printf("\nUsage: notify-gtk2 [n N sec] [eiqw] \"text message\"\n");
	printf("\n\t -e | --error \"message\"\n\t -i | --info \"message\"\n\t -q | --question \"question yes no\"\n\t -w | --warning \"warning yes no\"\n\t -n | --timeout N sec\n");
	
}

static struct option main_options[] = {
	{ "help", 0, 0, 'h' },
	{ "info", 0, 0, 'i' },
	{ "error", 0, 0, 'e' },
	{ "pic", 0, 0, 'p' },
	{ "question", 0, 0, 'q' },
	{ "start", 0, 0, 's' },
	{ "warning", 0, 0, 'w' },
	{ "timeout", 0, 0, 'n' },
	{ 0, 0, 0, 0 }
};

gboolean Exit() { exit (0); }
void YesFunc(){ exit(0); }
void NoFunc(){ exit(1); }
/*
int WaitOut (char *argv) {
	
	char line[6], prog[16] = "pidof ";
	FILE *fd;
	
	system (argv);
	strcat (prog, argv);
	while (cmd = popen(prog, "r")) {

	fgets(line, 6, cmd);
	pid_t pid = strtoul(line, NULL, 10);
	printf("%d\n", pid);
	pclose(cmd);
	sleep (1);
//	return (pid);
	}
}

GtkWidget *window (int t, char *img, char *msg) {
//	gtk_init(&argc, &argv);
	if (t) g_timeout_add (t, Exit, NULL);
	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_move(GTK_WINDOW(window), 50, 50);

	vbox = gtk_vbox_new (FALSE,0);
	gtk_container_add (GTK_CONTAINER (window), vbox);
	gtk_container_set_border_width (GTK_CONTAINER(window), 3);
	hbox = gtk_hbox_new (FALSE,0);
	
	image = gtk_image_new_from_file (img);
/*	pix = gtk_image_get_pixbuf (image);
	gtk_container_add (GTK_CONTAINER (hbox), image);
	image = gtk_image_new(); */
	
/*	gtk_widget_set_size_request (image, 80, 80); */
/*	pic = gtk_image_set_from_file (img, 80);
	pic = gtk_image_set_from_file (img, NULL);
	gtk_image_set_pixel_size (pic, 80); */
/*	image = gtk_image_set_from_image (pic, NULL, NULL);
	gtk_widget_set_size_request (image, 80, 80);
	gtk_frame_new (const gchar *label); */
/*	button = gtk_button_new_with_label(msg);
	
	if (yesno == 1) {
		hbox1 = gtk_hbox_new (FALSE,0);
		yes_button = gtk_button_new_from_stock (GTK_STOCK_YES);
		no_button = gtk_button_new_from_stock (GTK_STOCK_NO);
		gtk_box_pack_end (GTK_BOX (hbox1), no_button, FALSE, FALSE, 0);
		gtk_box_pack_end (GTK_BOX (hbox1), yes_button, FALSE, FALSE, 0);
		gtk_signal_connect (GTK_OBJECT (yes_button), "clicked", GTK_SIGNAL_FUNC (YesFunc), window);
		gtk_signal_connect (GTK_OBJECT (no_button), "clicked", GTK_SIGNAL_FUNC (NoFunc), window);
		
	}
    
	gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0); 
	if (yesno == 1) gtk_box_pack_start (GTK_BOX (vbox), hbox1, FALSE, FALSE, 0);
/* Клик по тексту закроет окно */	
/*	gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (YesFunc), window);

	gtk_widget_show_all(window);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
/*	gtk_main(); 
}*/

int WaitOut (char *argv) {
	
	char line[6], prog[16] = "pidof ";
	FILE *fd;
	pid_t pid;
	strcat (prog, argv);
	
	switch(pid=fork()) {
		case -1:
			exit(1);
		case 0:
/*			window (t, img, msg); */
			while (fd = popen(prog, "r")) {
				sleep (1);
			}
			pclose(fd);
			kill(getppid(),15);
			raise(15);
		default:
			system (argv);
			printf ("Ok\n");
			kill(pid,15);
		}	
	}

int main( int argc, char *argv[])
{
/*	GtkWidget *window, *image, *button, *hbox, *vbox, *hbox1, *yes_button, *no_button;
	int opt, t = 3000, yesno;
	char msg[128] = "\n ", img[40] = "/usr/share/pixmaps/"; */
	
	while ((opt=getopt_long(argc, argv, "ehiqwn:p:s:", main_options, NULL)) != -1) {
		switch(opt) {
			case 'i':
				strcat(img,"info.svg");
				break;
			case 'e':
				strcat(img,"error.svg");
				break;
			case 'q':
				strcat(img,"question.svg");
				yesno = 1;
				t = 0;
				break;
			case 'p':
				strcat(img,optarg);
				break;
			case 's':
				start = optarg;
				strcat(img,"wait.gif");
				t = 0;
				break;
			case 'w':
				strcat(img,"warning.svg");
				yesno = 1;
				t = 0;
				break;
			case 'n':
				t = (atoi(optarg) * 1000);
				break;
			case 'h':
				usage();
				exit(0);

			default:
				exit(1);
		}
	}
	
	argc -= optind;
	argv += optind;
	optind = 0;
	
	if (argc == 0) { usage(); exit(1); }
	
	strcat(msg,argv[0]);
	strcat(msg," \n");
//	if (start) WaitOut (start);
	gtk_init(&argc, &argv);
	if (t) g_timeout_add (t, Exit, NULL);
	window = gtk_window_new(GTK_WINDOW_POPUP);
	gtk_window_move(GTK_WINDOW(window), 50, 50);

	vbox = gtk_vbox_new (FALSE,0);
	gtk_container_add (GTK_CONTAINER (window), vbox);
	gtk_container_set_border_width (GTK_CONTAINER(window), 3);
	hbox = gtk_hbox_new (FALSE,0);
	
	image = gtk_image_new_from_file (img);
/*	pix = gtk_image_get_pixbuf (image);
	gtk_container_add (GTK_CONTAINER (hbox), image);
	image = gtk_image_new(); */
	
/*	gtk_widget_set_size_request (image, 80, 80); */
/*	pic = gtk_image_set_from_file (img, 80);
	pic = gtk_image_set_from_file (img, NULL);
	gtk_image_set_pixel_size (pic, 80); */
/*	image = gtk_image_set_from_image (pic, NULL, NULL);
	gtk_widget_set_size_request (image, 80, 80);
	gtk_frame_new (const gchar *label); */
	button = gtk_button_new_with_label(msg); 
	
	if (yesno == 1) {
		hbox1 = gtk_hbox_new (FALSE,0);
		yes_button = gtk_button_new_from_stock (GTK_STOCK_YES);
		no_button = gtk_button_new_from_stock (GTK_STOCK_NO);
		gtk_box_pack_end (GTK_BOX (hbox1), no_button, FALSE, FALSE, 0);
		gtk_box_pack_end (GTK_BOX (hbox1), yes_button, FALSE, FALSE, 0);
		gtk_signal_connect (GTK_OBJECT (yes_button), "clicked", GTK_SIGNAL_FUNC (YesFunc), window);
		gtk_signal_connect (GTK_OBJECT (no_button), "clicked", GTK_SIGNAL_FUNC (NoFunc), window);
		
	}
    
	gtk_box_pack_start (GTK_BOX (hbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (hbox), button, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0); 
	if (yesno == 1) gtk_box_pack_start (GTK_BOX (vbox), hbox1, FALSE, FALSE, 0);
/* Клик по тексту закроет окно */	
	gtk_signal_connect (GTK_OBJECT (button), "clicked", GTK_SIGNAL_FUNC (YesFunc), window); 

	gtk_widget_show_all(window);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL); 
//	if (start) WaitOut (start);
	gtk_main();
	
	return 0;
}