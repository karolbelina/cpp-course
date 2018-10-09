#pragma once

const std::string DEFAULT_NAME = "untitled";
const int DEFAULT_LENGTH = 10;
const int DEFAULT_VALUE = 0;


// --- strings ---
const std::string TITLE_MESSAGE = "table creator v1.0";
const std::string HELP_MESSAGE = "available commands:\n\tcreate <amount>\n\trename <table index> <name>\n\t"
								 "resize <table index> <size>\n\tremove <table index>\n\tremove all\n\tclone <table index>\n\t"
								 "status\n\tstatus <table index>\n\tedit <table index> <cell index> <value>\n\thelp\n\tquit";
const std::string ENTER_TABLE_NAME_MESSAGE = "enter the name of table #";
const std::string ENTER_TABLE_LENGTH_MESSAGE = "enter the length of table #";
const std::string COLON = ": ";
const std::string CREATED_TABLE_MESSAGE = "table created successfully";
const std::string REMOVED_TABLE_MESSAGE = "removed table #";
const std::string REMOVED_ALL_TABLES_MESSAGE = "removed all tables";
const std::string TABLE_LENGTH_MESSAGE = "the length of table #";
const std::string TABLE_NAME_MESSAGE = "the name of table #";
const std::string CELL_VALUE_MESSAGE = "the value of cell #";
const std::string OF_TABLE_MESSAGE = "of table #";
const std::string SET_TO_MESSAGE = " has been set to ";
const std::string CLONED_TABLE_MESSAGE = "cloned table #";

const std::string PROMPT_MESSAGE = "> ";

// errors
const std::string INDEX_OUT_OF_BOUNDS_MESSAGE = "index out of bounds";
const std::string INVALID_ARGUMENT_MESSAGE = "invalid argument";
const std::string OUT_OF_MEMORY_MESSAGE = "invalid argument";
const std::string INVALID_COMMAND_MESSAGE = "invalid command";
const std::string INVALID_AMOUNT_MESSAGE = "invalid amount";
const std::string INVALID_TABLE_LENGTH_MESSAGE = "invalid table length";
const std::string INVALID_TABLE_INDEX_MESSAGE = "invalid table index";
const std::string INVALID_CELL_INDEX_MESSAGE = "invalid cell index";
const std::string INVALID_VALUE_MESSAGE = "invalid value";
const std::string AMOUNT_GREATER_THAN_ZERO_MESSAGE = "amount must be greater than zero";
const std::string NO_PARAMETERS_MESSAGE = "no parameters";
const std::string NO_SECOND_PARAMETER_MESSAGE = "no second parameter";
const std::string NO_SECOND_AND_THIRD_PARAMETER_MESSAGE = "no second and third parameter";
const std::string NO_THIRD_PARAMETER_MESSAGE = "no third parameter";
const std::string UNKNOWN_ERROR_MESSAGE = "unknown error";

// commands
const std::string QUIT_COMMAND = "quit";
const std::string CREATE_COMMAND = "create";
const std::string REMOVE_COMMAND = "remove";
const std::string ALL_COMMAND = "all";
const std::string RESIZE_COMMAND = "resize";
const std::string RENAME_COMMAND = "rename";
const std::string STATUS_COMMAND = "status";
const std::string CLONE_COMMAND = "clone";
const std::string EDIT_COMMAND = "edit";
const std::string HELP_COMMAND = "help";

// tables
const std::string NOARG_CONSTRUCTOR_MESSAGE = "\tbezp: ";
const std::string PARAM_CONSTRUCTOR_MESSAGE = "\tparametr: ";
const std::string COPYING_CONSTRUCTOR_MESSAGE = "\tkopiuj: ";
const std::string DESTRUCTOR_MESSAGE = "\tusuwam: ";
const std::string COPY_STRING = "_copy";