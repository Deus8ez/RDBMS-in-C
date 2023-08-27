#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)
#define TABLE_MAX_PAGES 100
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
typedef struct {
  int file_descriptor;
  uint32_t file_length;
  void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct {
  uint32_t num_rows;
  Pager* pager;
} Table;

typedef struct {
  uint32_t id;
  char username[COLUMN_USERNAME_SIZE+1];
  char email[COLUMN_EMAIL_SIZE+1];
} Row;

typedef enum {
  META_COMMAND_SUCCESS,
  META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
  PREPARE_SUCCESS,
  PREPARE_NEGATIVE_ID,
  PREPARE_STRING_TOO_LONG,
  PREPARE_SYNTAX_ERROR,
  PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef struct {
  char* buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef enum { 
  STATEMENT_INSERT, 
  STATEMENT_SELECT 
} StatementType;

typedef struct {
  StatementType type;
  Row row_to_insert;
} Statement;

typedef enum { 
  EXECUTE_SUCCESS, 
  EXECUTE_TABLE_FULL 
} ExecuteResult;

typedef struct {
  Table* table;
  uint32_t row_num;
  bool end_of_table;  // Indicates a position one past the last element
} Cursor;