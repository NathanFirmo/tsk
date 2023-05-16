/* Our example parser states. */
enum state {
    STATE_START,   
    STATE_STREAM, 
    STATE_DOCUMENT,
    STATE_SECTION, 

    STATE_TASK_LIST,  
    STATE_TASK_ITEM, 
    STATE_TASK_ITEM_KEY,   

    STATE_STEP_LIST,
    STATE_STEP_ITEM, 
    STATE_STEP_ITEM_KEY,
    STATE_STEP_NAME,

    STATE_COMMAND_LIST,      
    STATE_COMMAND_ITEM,

    STATE_STOP
};

/* yaml_* functions return 1 on success and 0 on failure. */
enum status { SUCCESS = 1, FAILURE = 0 };
