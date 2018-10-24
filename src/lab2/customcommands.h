#pragma once

#include "command.h"
#include "tablecontainer.h"

class CustomCommand : public Command {
public:
	CustomCommand(TableContainer* tableContainer);

protected:
	void getString(std::string &destination);
	bool getInt(int &destination);
	TableContainer* tableContainer;
};

class CreateCommand : public CustomCommand {
public:
	CreateCommand(TableContainer* tableContainer);
	void runCommand();
};

class RemoveCommand : public CustomCommand {
public:
	RemoveCommand(TableContainer* tableContainer);
	void runCommand();
};

class RemoveAllCommand : public CustomCommand {
public:
	RemoveAllCommand(TableContainer* tableContainer);
	void runCommand();
};

class ResizeCommand : public CustomCommand {
public:
	ResizeCommand(TableContainer* tableContainer);
	void runCommand();
};

class RenameCommand : public CustomCommand {
public:
	RenameCommand(TableContainer* tableContainer);
	void runCommand();
};

class StatusCommand : public CustomCommand {
public:
	StatusCommand(TableContainer* tableContainer);
	void runCommand();
};

class StatusAllCommand : public CustomCommand {
public:
	StatusAllCommand(TableContainer* tableContainer);
	void runCommand();
};

class CloneCommand : public CustomCommand {
public:
	CloneCommand(TableContainer* tableContainer);
	void runCommand();
};

class EditCommand : public CustomCommand {
public:
	EditCommand(TableContainer* tableContainer);
	void runCommand();
};