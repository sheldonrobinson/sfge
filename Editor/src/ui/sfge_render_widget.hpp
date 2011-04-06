#ifndef SFGE_EDITOR_UI_SFGE_RENDER_WIDGET_HPP
#define SFGE_EDITOR_UI_SFGE_RENDER_WIDGET_HPP

#include <QtGui/QWidget>
#include <QtGui/QPaintEvent>

#include <sfge/infrastructure/game.hpp>

class SFGERenderWidget : public QWidget, public sfge::Game
{
	Q_OBJECT

public:
	SFGERenderWidget(QWidget *parent = nullptr);

protected:
	virtual QPaintEngine*	paintEngine() const override;

	virtual void paintEvent(QPaintEvent *evt) override;
	virtual void resizeEvent(QResizeEvent *evt) override;

private:
	void	InitSFGE();

private:
	bool	mSFGEInitialized;
};

#endif
