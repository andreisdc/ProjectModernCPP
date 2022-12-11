#pragma once

#include <QtGui>
#include <Qtcore>
#include <QDialog>
#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected slots:
	void on_buttonStartpageLogin_clicked();
	void on_buttonStartpageSignup_clicked();

	void on_buttonLoginBack_clicked();
	void on_buttonSignupBack_clicked();

	void on_buttonLoginLogin_clicked();
	void on_buttonSignupSignup_clicked();

	void on_radioButtonLoginShowPassword_released();
	void on_radioButtonSignupShowPassword_released();

	void on_Test_clicked();

	void on_buttonLobbyKickplayer1_clicked();
	void on_buttonLobbyKickplayer2_clicked();
	void on_buttonLobbyKickplayer3_clicked();

	void on_buttonLobbyAddplayer_clicked();
	void on_buttonLobbyStart_clicked();

	void on_buttonWindowInviteAdd_clicked();

	void on_buttonLobbyLogout_clicked();

	void setAllPoints();

	void on_buttonGameCounty1_clicked();
	void on_buttonGameCounty2_clicked();
	void on_buttonGameCounty3_clicked();
	void on_buttonGameCounty4_clicked();
	void on_buttonGameCounty5_clicked();
	void on_buttonGameCounty6_clicked();
	void on_buttonGameCounty7_clicked();
	void on_buttonGameCounty8_clicked();
	void on_buttonGameCounty9_clicked();
	void on_buttonGameCounty10_clicked();
	void on_buttonGameCounty11_clicked();
	void on_buttonGameCounty12_clicked();
	void on_buttonGameCounty13_clicked();
	void on_buttonGameCounty14_clicked();
	void on_buttonGameCounty15_clicked();

	void on_buttonQuestionA_clicked();
	void on_buttonQuestionB_clicked();
	void on_buttonQuestionC_clicked();
	void on_buttonQuestionD_clicked();

	void on_buttonQuestionNumberEnter_clicked();

	void changePassword();

private:
	Ui::MainWindowClass ui;
	QString initialPoints = "100";
};
