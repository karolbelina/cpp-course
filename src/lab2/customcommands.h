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
	void runCommand() override final;
};

class RemoveCommand : public CustomCommand {
public:
	RemoveCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class RemoveAllCommand : public CustomCommand {
public:
	RemoveAllCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class ResizeCommand : public CustomCommand {
public:
	ResizeCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class RenameCommand : public CustomCommand {
public:
	RenameCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class StatusCommand : public CustomCommand {
public:
	StatusCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class StatusAllCommand : public CustomCommand {
public:
	StatusAllCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class CloneCommand : public CustomCommand {
public:
	CloneCommand(TableContainer* tableContainer);
	void runCommand() override final;
};

class EditCommand : public CustomCommand {
public:
	EditCommand(TableContainer* tableContainer);
	void runCommand() override final;
};