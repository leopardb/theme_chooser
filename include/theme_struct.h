
#ifndef THEME_STRUCT_H
#define THEME_STRUCT_H

struct Theme
{
	char* ThemeName;
	char* IconThemeName;
	char* CursorThemeName;
	char* SoundThemeName;
	char* Background;
	char* Theme;
};

void freeThemeStruct(struct Theme* theme);

#endif