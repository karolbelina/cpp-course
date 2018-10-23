#pragma once

#include "command.h"
#include "tablecontainer.h"

class CustomCommand : public Command {
public:
	CustomCommand(TableContainer* tableContainer);

protected:
	TableContainer* tableContainer;
};

class CreateCommand : public CustomCommand {
public:
	CreateCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class RemoveCommand : public CustomCommand {
public:
	RemoveCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class ResizeCommand : public CustomCommand {
public:
	ResizeCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class RenameCommand : public CustomCommand {
public:
	RenameCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class StatusCommand : public CustomCommand {
public:
	StatusCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class CloneCommand : public CustomCommand {
public:
	CloneCommand(TableContainer* tableContainer);
	virtual void runCommand();
};

class EditCommand : public CustomCommand {
public:
	EditCommand(TableContainer* tableContainer);
	virtual void runCommand();
};