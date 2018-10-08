#pragma once

const std::string DEFAULT_NAME = "untitled";	// char* const
const int DEFAULT_LENGTH = 10;
const int DEFAULT_VALUE = 0;

const std::string COPY_STRING = "_copy";

const std::string TITLE_MESSAGE = "table creator v1.0";
const std::string HELP_MESSAGE = "available commands:\n\tcreate <amount>\n\trename <table index> <name>\n\t"
								 "resize <table index> <size>\n\tremove <table index>\n\tremove all\n\tclone <table index>\n\t"
								 "status\n\tstatus <table index>\n\tedit <table index> <cell index> <value>\n\thelp\n\tquit";
const std::string PROMPT_MESSAGE = "> ";
const std::string ENTER_TABLE_NAME_MESSAGE = "enter the name of table #";
const std::string ENTER_TABLE_LENGTH_MESSAGE = "enter the length of table #";
const std::string COLON = ": ";



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


const std::string NOARG_CONSTRUCTOR_MESSAGE = "\tbezp: ";
const std::string PARAM_CONSTRUCTOR_MESSAGE = "\tparametr: ";
const std::string COPYING_CONSTRUCTOR_MESSAGE = "\tkopiuj: ";
const std::string DESTRUCTOR_MESSAGE = "\tusuwam: ";