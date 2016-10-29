
//#include <stdlib.h>

#include <gtk/gtk.h>
#include "theme_struct.h"
#include "xml_functions.h"
#include "xfconf_functions.h"

#include <stdlib.h>
#include <string.h>



static void setTheme (GtkWidget *widget, gpointer data)
{
	const gchar* activeId = gtk_combo_box_get_active_id (GTK_COMBO_BOX(widget));

	struct Theme theme;

	theme.ThemeName = strdup(activeId);
	theme.IconThemeName = strdup(activeId);
	theme.CursorThemeName = strdup(activeId);
	theme.SoundThemeName = strdup(activeId);

	char* background = malloc(27+sizeof(char)*strlen(activeId));
	strcpy(background, "/usr/share/wallpapers/");
	strcat(background, theme.ThemeName);
	strcat(background, ".jpg");

	theme.Background = background;

	theme.Theme = strdup(activeId);

	setCurrentTheme(&theme);
		
	freeThemeStruct(&theme);	
}



static void loadThemeFromFile (GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File",
		                                  GTK_WINDOW (data),
		                                  action,
		                                  ("_Cancel"),
		                                  GTK_RESPONSE_CANCEL,
		                                  ("_Open"),
		                                  GTK_RESPONSE_ACCEPT,
		                                  NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	  {
		char *filename;
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		filename = gtk_file_chooser_get_filename (chooser);

		struct Theme theme;

		loadTheme(&theme,filename);
		setCurrentTheme(&theme);
		freeThemeStruct(&theme);

		g_free (filename);
	  }

	gtk_widget_destroy (dialog);
}


static void saveThemeToFile (GtkWidget *widget, gpointer data)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",
											GTK_WINDOW (data),
											action,
											("_Cancel"),
											GTK_RESPONSE_CANCEL,
											("_Save"),
											GTK_RESPONSE_ACCEPT,
											NULL);
	chooser = GTK_FILE_CHOOSER (dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

	gtk_file_chooser_set_current_name (chooser,("Untitled document"));

	res = gtk_dialog_run (GTK_DIALOG (dialog));

	if (res == GTK_RESPONSE_ACCEPT)
	{
		char* filename = gtk_file_chooser_get_filename (chooser);

		struct Theme currentTheme;

		getCurrentTheme(&currentTheme);
		saveTheme(&currentTheme, filename);
		freeThemeStruct(&currentTheme);

		g_free (filename);
	}

	gtk_widget_destroy (dialog);
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
	GtkWidget *window;
	GtkWidget *themeComboBox;
	GtkWidget *loadButton;
	GtkWidget *saveButton;
	GtkWidget *closeButton;
	GtkWidget *button_box;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Theme Settings");
	gtk_window_set_default_size (GTK_WINDOW (window), 400, 200);

	button_box = gtk_button_box_new (GTK_ORIENTATION_VERTICAL);
	gtk_container_add (GTK_CONTAINER (window), button_box);

	themeComboBox = gtk_combo_box_text_new ();

	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Baseball", "Baseball");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "DangerousCreatures", "Dangerous Creatures");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "InsideYourComputer", "Inside your Computer");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Jungle", "Jungle");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "LeonardoDaVinci", "Leonardo Da Vinci");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "MoreWindows", "More Windows");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Mystery", "Mystery");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Nature", "Nature");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Science", "Science");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Space", "Space");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Sports", "Sports");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "The60sUSA", "The 60s in the USA");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "TheGoldenEra", "The Golden Era");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Travel", "Travel");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Underwater", "Underwater");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "Windows98", "Windows 98");
	gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(themeComboBox), "WindowsClassic", "Windows Classic");

	gtk_combo_box_set_active_id (GTK_COMBO_BOX(themeComboBox), "Baseball");

	g_signal_connect (themeComboBox, "changed", G_CALLBACK (setTheme), NULL);
	

	saveButton = gtk_button_new_with_label ("Save current theme to file");
	g_signal_connect (saveButton, "clicked", G_CALLBACK (saveThemeToFile), window);

	loadButton = gtk_button_new_with_label ("Load a theme from file");
	g_signal_connect (loadButton, "clicked", G_CALLBACK (loadThemeFromFile), window);

	closeButton = gtk_button_new_with_label ("Close that shit");
	g_signal_connect_swapped (closeButton, "clicked", G_CALLBACK (gtk_widget_destroy), window);

	gtk_container_add (GTK_CONTAINER (button_box), saveButton);
	gtk_container_add (GTK_CONTAINER (button_box), loadButton);
	gtk_container_add (GTK_CONTAINER (button_box), themeComboBox);
	gtk_container_add (GTK_CONTAINER (button_box), closeButton);

	gtk_widget_show_all (window);
}

int
main (int    argc,
      char **argv)
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("com.github.leopardb.theme_chooser", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
