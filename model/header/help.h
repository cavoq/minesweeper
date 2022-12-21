#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui { class Help; }

/**
 * @class Help
 * @brief The Help class is a dialog box that displays information about how to play the game.
 *
 * The Help class is a subclass of QDialog, which is a Qt widget used for building dialog boxes. It displays information about how to play the game in a window that can be opened and closed by the user. The class provides a public constructor for creating a new `Help` object, and a public destructor for cleaning up when the object is no longer needed.
 */
class Help : public QDialog
{
    Q_OBJECT

public:

    /**
     * Constructs a new `Help` dialog with the given parent widget.
     * @param parent the parent widget
     */
    explicit Help(QWidget *parent = nullptr);

    /**
     * Destructor for `Help`.
     */
    ~Help();

private:

    /**
     * The user interface for the `Help` dialog.
     */
    Ui::Help *ui;
};

#endif // HELP_H
