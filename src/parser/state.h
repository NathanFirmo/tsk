/* Our example parser states. */
enum state {
    STATE_START,    /* start state */
    STATE_STREAM,   /* start/end stream */
    STATE_DOCUMENT, /* start/end document */
    STATE_SECTION,  /* top level */

    STATE_TLIST,   /* fruit list */
    STATE_TVALUES, /* fruit key-value pairs */
    STATE_TKEY,    /* fruit key */
    STATE_TNAME,   /* fruit name value */

    STATE_SLIST,   /* steps list */
    STATE_SVALUES, /* step key-value pairs */
    STATE_SKEY,    /* step key */
    STATE_SNAME,   /* strp name */

    STATE_SCOMMAND,        /* step command */
    STATE_SCOMMAND_VALUES, /* step command values */

    STATE_STOP /* end state */
};

/* yaml_* functions return 1 on success and 0 on failure. */
enum status { SUCCESS = 1, FAILURE = 0 };
