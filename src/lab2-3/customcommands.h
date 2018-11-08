#pragma once

#include "command.h"
#include "tablecontainer.h"

class CustomCommand : public menu::Command {
public:
	CustomCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;

protected:
	table::TableContainer* tableContainer;
};

class CreateCommand : public CustomCommand {
public:
	CreateCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class RemoveCommand : public CustomCommand {
public:
	RemoveCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class RemoveAllCommand : public CustomCommand {
public:
	RemoveAllCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class ResizeCommand : public CustomCommand {
public:
	ResizeCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class RenameCommand : public CustomCommand {
public:
	RenameCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class StatusCommand : public CustomCommand {
public:
	StatusCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class StatusAllCommand : public CustomCommand {
public:
	StatusAllCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class CloneCommand : public CustomCommand {
public:
	CloneCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};

class EditCommand : public CustomCommand {
public:
	EditCommand(table::TableContainer* tableContainer);
	virtual Command* clone() const override;
	void runCommand() const override final;
};