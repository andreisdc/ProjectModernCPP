#pragma once

#include <QtGui>
#include <Qtcore>
#include <QDialog>
#include "ui_MainWindow.h"
#include <QtWidgets/QMainWindow>
#include "Session.hpp"
#include "User.hpp"
#include <ctime>
#include <cstdlib>
#include "Lobby.hpp"
#include "MyThread.hpp"
#include <thread>
#include <nlohmann/json.hpp>
#include <fstream>
#include <random>
#include <set>

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

	void on_buttonMainMenuCreateGame_clicked();
	void on_buttonMainMenuJoinGame_clicked();

	void on_radioButtonLoginShowPassword_released();
	void on_radioButtonSignupShowPassword_released();

	void on_buttonLobbyLogout_clicked();
	void on_buttonLobbyKickplayer1_clicked();
	void on_buttonLobbyKickplayer2_clicked();
	void on_buttonLobbyKickplayer3_clicked();

	void on_buttonLobbyStart_clicked();

	void setAllPoints();


	void on_buttonQuestionA_clicked();
	void on_buttonQuestionB_clicked();
	void on_buttonQuestionC_clicked();
	void on_buttonQuestionD_clicked();

	void on_buttonQuestionNumberEnter_clicked();

	void on_buttonSatuMare3x3_clicked();
	void on_buttonMoldova3x3_clicked();
	void on_buttonTimisoara3x3_clicked();
	void on_buttonArdeal3x3_clicked();
	void on_buttonTransilvania3x3_clicked();
	void on_buttonOltenia3x3_clicked();
	void on_buttonMuntenia3x3_clicked();
	void on_buttonDobrogea3x3_clicked();
	void on_buttonMaramures3x3_clicked();
	void on_buttonSatuMare5x3_clicked();
	void on_buttonMaramures5x3_clicked();
	void on_buttonIasi5x3_clicked();
	void on_buttonTimisoara5x3_clicked();
	void on_buttonCluj5x3_clicked();
	void on_buttonTransilvania5x3_clicked();
	void on_buttonBrasov5x3_clicked();
	void on_buttonGalati5x3_clicked();
	void on_buttonBanat5x3_clicked();
	void on_buttonOltenia5x3_clicked();
	void on_buttonTeleorman5x3_clicked();
	void on_buttonBucuresti5x3_clicked();
	void on_buttonCalarasi5x3_clicked();
	void on_buttonTulcea5x3_clicked();
	void on_buttonConstanta5x3_clicked();
	void on_buttonSatuMare6x4_clicked();
	void on_buttonMaramures6x4_clicked();
	void on_buttonSuceava6x4_clicked();
	void on_buttonBotosani6x4_clicked();
	void on_buttonBihor6x4_clicked();
	void on_buttonCluj26x4_clicked();
	void on_buttonCluj6x4_clicked();
	void on_buttonHarghita6x4_clicked();
	void on_buttonIasi6x4_clicked();
	void on_buttonArad6x4_clicked();
	void on_buttonBanat6x4_clicked();
	void on_buttonHunedoara6x4_clicked();
	void on_buttonAlba6x4_clicked();
	void on_buttonSibiu6x4_clicked();
	void on_buttonBrasov6x4_clicked();
	void on_buttonGalati6x4_clicked();
	void on_buttonCarasSevarin6x4_clicked();
	void on_buttonMehedinti6x4_clicked();
	void on_buttonTeleorman6x4_clicked();
	void on_buttonBucuresti6x4_clicked();
	void on_buttonBraila6x4_clicked();
	void on_buttonCalarasi6x4_clicked();
	void on_buttonTulcea6x4_clicked();
	void on_buttonConstanta6x4_clicked();

	void changePassword();

	void VerifyPlayer();
	void ConnectButton(int nrPlayer);
	
	//parte de logica jocului

	void StartGame(int nrPlayer);
	void verify_ans(std::string ans);
	void AfterRegionSelect(const std::string& regionName);
	int addPoints(std::string points);

private:
	Ui::MainWindowClass ui;
	QString initialPoints = "100";
	QPushButton *SatuMare3x3;
	QPushButton *Moldova3x3;
	QPushButton *Timisoara3x3;
	QPushButton *Ardeal3x3;
	QPushButton *Transilvania3x3;
	QPushButton *Oltenia3x3;
	QPushButton *Muntenia3x3;
	QPushButton *Dobrogea3x3;
	QPushButton *Maramures3x3;
	QPushButton *SatuMare5x3;
	QPushButton *Maramures5x3;
	QPushButton *Iasi5x3;
	QPushButton *Timisoara5x3;
	QPushButton *Cluj5x3;
	QPushButton *Transilvania5x3;
	QPushButton *Brasov5x3;
	QPushButton *Galati5x3;
	QPushButton *Banat5x3;
	QPushButton *Oltenia5x3;
	QPushButton *Teleorman5x3;
	QPushButton *Bucuresti5x3;
	QPushButton *Calarasi5x3;
	QPushButton *Tulcea5x3;
	QPushButton *Constanta5x3;
	QPushButton *SatuMare6x4;
	QPushButton *Maramures6x4;
	QPushButton *Suceava6x4;
	QPushButton *Botosani6x4;
	QPushButton *Bihor6x4;
	QPushButton *Cluj26x4;
	QPushButton *Cluj6x4;
	QPushButton *Harghita6x4;
	QPushButton *Iasi6x4;
	QPushButton *Arad6x4;
	QPushButton *Banat6x4;
	QPushButton *Hunedoara6x4;
	QPushButton *Alba6x4;
	QPushButton *Sibiu6x4;
	QPushButton *Brasov6x4;
	QPushButton *Galati6x4;
	QPushButton *CarasSevarin6x4;
	QPushButton *Mehedinti6x4;
	QPushButton *Teleorman6x4;
	QPushButton *Bucuresti6x4;
	QPushButton *Braila6x4;
	QPushButton *Calarasi6x4;
	QPushButton *Tulcea6x4;
	QPushButton *Constanta6x4;

	std::vector<QPushButton*> listButtons3x3;
	std::vector<QPushButton*> listButtons5x3;
	std::vector<QPushButton*> listButtons6x4;
	
	Session session;
	User user1;
	User user2;
	User user3;
	User user4;

	MyThread myThread;
	nlohmann::json intrebariSimple;
	nlohmann::json intrebariNumere;


	std::uniform_int_distribution<int> distSimple;
	std::uniform_int_distribution<int> distNumber;
	std::mt19937 mt;
	std::set<int> randomNumbersSimpleHistory;
	std::set<int> randomNumbersNumberHistory;

	std::string answerNumberUser1;
	std::string answerNumberUser2;
	std::string answerNumberUser3;
	std::string answerNumberUser4;


	int generateRandomSimpleNumber();
	int generateRandomNumberNumber();
	void getQuestionNumber();
};
