
#ifndef XFCONF_FUNCTIONS_H
#define XFCONF_FUNCTIONS_H

void xfconf_query_printerr(const gchar *message, ...);
void randomxfconfstuff();
void getCurrentTheme(struct Theme* currentTheme);
void setCurrentTheme(const struct Theme* theme);

#endif