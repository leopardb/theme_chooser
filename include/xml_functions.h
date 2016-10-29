
#ifndef XML_FUNCTIONS_H
#define XML_FUNCTIONS_H

void parseDoc(char *docname);
void loadTheme(struct Theme* theme, char* filename);
void saveTheme(const struct Theme* theme, char* filename);

#endif