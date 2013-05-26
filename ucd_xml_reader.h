/*
 * ucdXmlReader.h
 *
 * Author: Paweł Parafiński <ppablo28@gmail.com>
 */

#ifndef UCDXMLREADER_H_
#define UCDXMLREADER_H_

#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

/* Constants containing XML tags */
struct XmlTag {
  const char *COMMENT_LINE;
  const char *SUBTITLE;
  const char *TITLE;
  const char *FILE_COMMENT;
  const char *NOTICE_LINE;
  const char *CHAR_ENTRY;
  const char *FORMALALIAS_LINE;
  const char *BLOCK_HEADER;
  const char *BLOCK_SUBHEADER;
  const char *VARIATION_LINE;
  const char *DECOMPOSITION;
  const char *COMPAT_MAPPING;
  const char *ALIAS_LINE;
  const char *ROOT;
  const char *CROSS_REF;
};

/* Constants containing XML attributes */
struct XmlAttr {
  const char *COMPAT;
  const char *BLOCK_END;
  const char *NAME;
  const char *WITH_ASTERISK;
  const char *TYPE;
  const char *CODE_POINT;
  const char *BLOCK_START;
  const char *VARIATION;
  const char *CONTENT;
  const char *REF;
  const char *DECOMP;
};

/* Constants containing Yes/No values */
struct YesNo {
  const char *YES;
  const char *NO;
};

extern const struct XmlTag xmlTags;
extern const struct XmlAttr xmlAttrs;
extern const struct YesNo yesNoValues;

/* A simple structure for XML tags */
struct tag_attr {
  const char *name;
  const char *value;
  struct tag_attr *next;
};

/* A container for all information connected with character entries and blocks (notice lines,
 * crossed references, aliases, etc. */
struct simple_tag {
  const char *name;
  const char *content;
  struct tag_attr *info;
  struct simple_tag *next;
};

/* The info about a char. It has a handle for the next char in the block */
struct char_entry {
  const char *name;
  unsigned long cp;
  const char *type;
  struct simple_tag *char_info;
  struct char_entry *next;
};

struct subheader_block {
  unsigned long start;
  unsigned long end;
  const char *name;
  struct simple_tag *outer_tags;
  struct char_entry *chars;
  struct subheader_block* next;
};

/* The structure of a block (with start and end for better search results) */
struct header_block {
  unsigned long start;
  unsigned long end;
  const char *name;
  struct char_entry *chars;
  struct simple_tag *outer_tags;
  struct subheader_block* subheaders;
  struct header_block *next;
};

/* Parse the XML DOM returned by the libxml to the convenient representation of UCD data */
struct header_block *parse_ucd_from_xml(const xmlNode *root);

/* Find the block with given character code point */
const struct header_block* find_ucd_block(const struct header_block* first,
    const unsigned long cp);

#endif /* UCDXMLREADER_H_ */
