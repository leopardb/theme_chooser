
#include "theme_struct.h"
#include "xfconf/xfconf.h"

#include <string.h>
#include <stdio.h>



void xfconf_query_printerr(const gchar *message, ...)
{
    va_list args;
    gchar *str;

    va_start(args, message);
    str = g_strdup_vprintf(message, args);
    va_end(args);

    g_printerr("%s.\n", str);
    g_free(str);
}


void getCurrentTheme(struct Theme* currentTheme)
{
	GError *error= NULL;

    if(!xfconf_init(&error))
    {
        xfconf_query_printerr(("Failed to init libxfconf: %s"), error->message);
        g_error_free(error);
    }


	XfconfChannel* channel = xfconf_channel_get("xsettings");

	gchar* themename = xfconf_channel_get_string(channel,"/Net/ThemeName","error");
	currentTheme->ThemeName = strdup(themename);
	g_free(themename);

	gchar* iconthemename = xfconf_channel_get_string(channel,"/Net/IconThemeName","error");
	currentTheme->IconThemeName = strdup(iconthemename);
	g_free(iconthemename);

	gchar* cursorthemetame = xfconf_channel_get_string(channel,"/Gtk/CursorThemeName","error");
	currentTheme->CursorThemeName = strdup(cursorthemetame);
	g_free(cursorthemetame);

	gchar* soundthemename = xfconf_channel_get_string(channel,"/Net/SoundThemeName","error");
	currentTheme->SoundThemeName = strdup(soundthemename);
	g_free(soundthemename);


	channel = xfconf_channel_get("xfce4-desktop");

	gchar* imagepath = xfconf_channel_get_string(channel,"/backdrop/screen0/monitor0/image-path","error");
	currentTheme->Background = strdup(imagepath);
	g_free(imagepath);


	channel = xfconf_channel_get("xfwm4");

	gchar* theme = xfconf_channel_get_string(channel,"/general/theme","error");
	currentTheme->Theme = strdup(theme);
	g_free(theme);

}


void setCurrentTheme(const struct Theme* theme)
{
	GError *error= NULL;

    if(!xfconf_init(&error))
    {
        xfconf_query_printerr(("Failed to init libxfconf: %s"), error->message);
        g_error_free(error);
    }


	XfconfChannel* channel = xfconf_channel_get("xsettings");

	xfconf_channel_set_string(channel,"/Net/ThemeName",theme->ThemeName);
	xfconf_channel_set_string(channel,"/Net/IconThemeName",theme->IconThemeName);
	xfconf_channel_set_string(channel,"/Gtk/CursorThemeName",theme->CursorThemeName);
	xfconf_channel_set_string(channel,"/Net/SoundThemeName",theme->SoundThemeName);

	//TODO use the pulseaudio helper functions, i'm too lazy right now...

	char command[50];

	sprintf(command, "upload-samples %s", theme->SoundThemeName);

	printf("%s\n", command);

	system(command);


	channel = xfconf_channel_get("xfce4-desktop");

	xfconf_channel_set_string(channel,"/backdrop/screen0/monitor0/image-path",theme->Background);

	channel = xfconf_channel_get("xfwm4");

	xfconf_channel_set_string(channel,"/general/theme",theme->Theme);
}


void randomxfconfstuff()
{
	GError *error= NULL;

    if(!xfconf_init(&error))
    {
        xfconf_query_printerr(("Failed to init libxfconf: %s"), error->message);
        g_error_free(error);
    }

/*XfconfChannel *xfconf_channel_new(const gchar *channel_name) G_GNUC_WARN_UNUSED_RESULT;*/

	XfconfChannel* channel = xfconf_channel_new("xsettings");


	const gchar *property = "/Net/IconThemeName";
	const gchar *value = "Baseball";

/*gchar *xfconf_channel_get_string(XfconfChannel *channel,
                                 const gchar *property,
                                 const gchar *default_value) G_GNUC_WARN_UNUSED_RESULT;*/

	//g_print (xfconf_channel_get_string(channel,property,value));

/*gboolean xfconf_channel_set_string(XfconfChannel *channel,
                                   const gchar *property,
                                   const gchar *value);*/

	//xfconf_channel_set_string(channel,property,value);
}
