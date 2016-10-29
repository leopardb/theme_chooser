
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "theme_struct.h"


void loadTheme(struct Theme* theme, char* filename)
{

	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(filename);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "xfcetheme")) {
		fprintf(stderr,"document of the wrong type, root node != xfcetheme");
		xmlFreeDoc(doc);
		return;
	}
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL) 
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"ThemeName")))
		{
			xmlChar* themename = xmlNodeGetContent(cur);
			theme->ThemeName = strdup(themename);
			xmlFree(themename);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"IconThemeName")))
		{
			xmlChar* iconthemename = xmlNodeGetContent(cur);
			theme->IconThemeName = strdup(iconthemename);
			xmlFree(iconthemename);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"CursorThemeName")))
		{
			xmlChar* cursorthemename = xmlNodeGetContent(cur);
			theme->CursorThemeName = strdup(cursorthemename);
			xmlFree(cursorthemename);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"SoundThemeName")))
		{
			xmlChar* soundthemename = xmlNodeGetContent(cur);
			theme->SoundThemeName = strdup(soundthemename);
			xmlFree(soundthemename);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"Background")))
		{
			xmlChar* background = xmlNodeGetContent(cur);
			theme->Background = strdup(background);
			xmlFree(background);
		}

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"Theme")))
		{
			xmlChar* themename = xmlNodeGetContent(cur);
			theme->Theme = strdup(themename);
			xmlFree(themename);
		}
		 
		cur = cur->next;
	}
	
	xmlFreeDoc(doc);
	return;
}


void saveTheme(struct Theme* theme, char* filename)
{
	xmlDocPtr doc = xmlNewDoc("1.0");

//xmlNodePtr	xmlNewNode		(xmlNsPtr ns, const xmlChar * name)

	xmlNodePtr cur = xmlNewNode(NULL, "xfcetheme");

/*xmlNodePtr	xmlNewDocNode		(xmlDocPtr doc, 
					 xmlNsPtr ns, 
					 const xmlChar * name, 
					 const xmlChar * content)*/
	//xmlNodePtr cur = xmlNewDocNode(doc, NULL, "IconThemeName", "toto");

//xmlNodePtr	xmlDocGetRootElement	(const xmlDoc * doc)
//xmlNodePtr	xmlDocSetRootElement	(xmlDocPtr doc,  xmlNodePtr root)
	xmlNodePtr oldrootNode = xmlDocSetRootElement(doc, cur);

	if (oldrootNode != NULL) {
		fprintf(stderr,"there was already a root node\n");
		xmlFreeDoc(doc);
		return;
	}

/*xmlNodePtr	xmlNewChild		(xmlNodePtr parent, 
					 xmlNsPtr ns, 
					 const xmlChar * name, 
					 const xmlChar * content)*/

/*xmlNodePtr	xmlNewTextChild		(xmlNodePtr parent, 
					 xmlNsPtr ns, 
					 const xmlChar * name, 
					 const xmlChar * content)*/


	xmlNewChild(cur, NULL, "ThemeName", theme->ThemeName);
	xmlNewChild(cur, NULL, "IconThemeName", theme->IconThemeName);
	xmlNewChild(cur, NULL, "CursorThemeName", theme->CursorThemeName);
	xmlNewChild(cur, NULL, "SoundThemeName", theme->SoundThemeName);
	xmlNewChild(cur, NULL, "Background", theme->Background);
	xmlNewChild(cur, NULL, "Theme", theme->Theme);

	xmlSaveFormatFile (filename, doc, 1);
	xmlFreeDoc(doc);
}


void parseDoc(char *docname)
{

	xmlDocPtr doc;
	xmlNodePtr cur;
	xmlChar *key;

	doc = xmlParseFile(docname);
	
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return;
	}
	
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return;
	}
	
	if (xmlStrcmp(cur->name, (const xmlChar *) "xfcetheme")) {
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return;
	}

/*xmlNodePtr	xmlNewChild		(xmlNodePtr parent, 
					 xmlNsPtr ns, 
					 const xmlChar * name, 
					 const xmlChar * content)*/

	//xmlNewTextChild (cur, NULL, "IconThemeName", "Mystery");

/*void	xmlNodeSetContent		(xmlNodePtr cur, 
					 const xmlChar * content)*/
	
	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		if ((!xmlStrcmp(cur->name, (const xmlChar *)"IconThemeName"))){
		    /*key = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
		    printf("keyword: %s\n", key);
		    xmlFree(key);*/

			xmlNodeSetContent(cur, "Mystery");
		}
		 
		cur = cur->next;
	}


	if (doc != NULL) {
		xmlSaveFormatFile (docname, doc, 0);
		xmlFreeDoc(doc);
	}

}
