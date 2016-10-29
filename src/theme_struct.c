
#include <stdlib.h>
#include "theme_struct.h"

void freeThemeStruct(struct Theme* theme)
{

	free(theme->ThemeName);
	free(theme->IconThemeName);
	free(theme->CursorThemeName);
	free(theme->SoundThemeName);
	free(theme->Background);
	free(theme->Theme);
}