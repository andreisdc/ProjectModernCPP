#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFrame>
#include <QPixmap>
#include <QPushButton>
#include <QStyle>
#include <QThread>
#include <cmath>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

QPushButton *createMaskedPushButton(const QString &label,
									const QString &path,
									QWidget *parent,
									int x,
									int y,
									int width,
									int height) {
	QImage img;
	img.load(path);
	auto newPushButton = new QPushButton(label, parent);
	newPushButton->setGeometry(QRect(QPoint(x + 210, y + 170), QSize(width, height)));
	QPixmap pixmap = QPixmap::fromImage(img).scaled(width, height, Qt::KeepAspectRatio);
	newPushButton->setStyleSheet("background-color:gray; border:0;");
	newPushButton->setMask(pixmap.mask());
	newPushButton->setCursor(Qt::PointingHandCursor);

	return newPushButton;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);

	std::ifstream f("intrebari.json");
	nlohmann::json intrebari = nlohmann::json::parse(f);
	f.close();

	this->intrebariSimple = intrebari["Standard questions"];
	this->intrebariNumere = intrebari["Numerical questions"];
	std::random_device rd;
	this->mt = std::mt19937(rd());
	this->distSimple = std::uniform_int_distribution<int>(0, this->intrebariSimple.size() - 1);
	this->distNumber = std::uniform_int_distribution<int>(0, this->intrebariNumere.size() - 1);

	user1 = User("Andrei", 100);
	user2 = User("Teo", 100);
	user3 = User("Alex", 100);
	user4 = User("Calin", 100);

	session = Session(&user1, &user2, &user3, &user4);

	this->SatuMare3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Satu Mare.png", this->ui.Game2Pers, 144, 20, 221, 229);
	this->Maramures3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Maramures.png", this->ui.Game2Pers, 347, 22, 242, 133);
	this->Moldova3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Moldova.png", this->ui.Game2Pers, 529, 2, 228, 359);
	this->Timisoara3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Timisoara.png", this->ui.Game2Pers, 1, 155, 186, 305);
	this->Ardeal3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Ardeal Vest.png", this->ui.Game2Pers, 155, 83, 235, 275);
	this->Transilvania3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Transilvania.png", this->ui.Game2Pers, 336, 108, 283, 272);
	this->Oltenia3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Oltenia.png", this->ui.Game2Pers, 100, 353, 246, 252);
	this->Muntenia3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Muntenia.png", this->ui.Game2Pers, 291, 343, 448, 293);
	this->Dobrogea3x3 = createMaskedPushButton("100", ":/MainWindow/assets/3x3/Dobrogea.png", this->ui.Game2Pers, 662, 365, 237, 249);

	connect(SatuMare3x3, SIGNAL(clicked()), this, SLOT(on_buttonSatuMare3x3_clicked()));
	connect(Maramures3x3, SIGNAL(clicked()), this, SLOT(on_buttonMaramures3x3_clicked()));
	connect(Moldova3x3, SIGNAL(clicked()), this, SLOT(on_buttonMoldova3x3_clicked()));
	connect(Timisoara3x3, SIGNAL(clicked()), this, SLOT(on_buttonTimisoara3x3_clicked()));
	connect(Ardeal3x3, SIGNAL(clicked()), this, SLOT(on_buttonArdeal3x3_clicked()));
	connect(Transilvania3x3, SIGNAL(clicked()), this, SLOT(on_buttonTransilvania3x3_clicked()));
	connect(Oltenia3x3, SIGNAL(clicked()), this, SLOT(on_buttonOltenia3x3_clicked()));
	connect(Muntenia3x3, SIGNAL(clicked()), this, SLOT(on_buttonMuntenia3x3_clicked()));
	connect(Dobrogea3x3, SIGNAL(clicked()), this, SLOT(on_buttonDobrogea3x3_clicked()));

	listButtons3x3.push_back(SatuMare3x3);
	listButtons3x3.push_back(Maramures3x3);
	listButtons3x3.push_back(Moldova3x3);
	listButtons3x3.push_back(Timisoara3x3);
	listButtons3x3.push_back(Ardeal3x3);
	listButtons3x3.push_back(Transilvania3x3);
	listButtons3x3.push_back(Oltenia3x3);
	listButtons3x3.push_back(Muntenia3x3);
	listButtons3x3.push_back(Dobrogea3x3);

	this->SatuMare5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/SatuMare.png", this->ui.Game3Pers, 144, 20, 221, 229);
	this->Maramures5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Maramures.png", this->ui.Game3Pers, 347, 22, 242, 133);
	this->Iasi5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Iasi.png", this->ui.Game3Pers, 529, 2, 211, 231);
	this->Timisoara5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Timisoara.png", this->ui.Game3Pers, 6, 155, 181, 133);
	this->Cluj5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Cluj.png", this->ui.Game3Pers, 155, 83, 235, 275);
	this->Transilvania5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Transilvania.png", this->ui.Game3Pers, 336, 108, 227, 272);
	this->Brasov5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Brasov.png", this->ui.Game3Pers, 448, 227, 171, 153);
	this->Galati5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Galati.png", this->ui.Game3Pers, 561, 182, 196, 179);
	this->Banat5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Banat.png", this->ui.Game3Pers, 1, 275, 183, 185);
	this->Oltenia5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Oltenia.png", this->ui.Game3Pers, 100, 353, 246, 252);
	this->Teleorman5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Teleorman.png", this->ui.Game3Pers, 291, 355, 172, 271);
	this->Bucuresti5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Bucuresti.png", this->ui.Game3Pers, 445, 357, 162, 279);
	this->Calarasi5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Calarasi.png", this->ui.Game3Pers, 569, 343, 170, 238);
	this->Tulcea5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Tulcea.png", this->ui.Game3Pers, 707, 365, 192, 142);
	this->Constanta5x3 = createMaskedPushButton("100", ":/MainWindow/assets/5x3/Constanta.png", this->ui.Game3Pers, 662, 472, 155, 142);

	connect(SatuMare5x3, SIGNAL(clicked()), this, SLOT(on_buttonSatuMare5x3_clicked()));
	connect(Maramures5x3, SIGNAL(clicked()), this, SLOT(on_buttonMaramures5x3_clicked()));
	connect(Iasi5x3, SIGNAL(clicked()), this, SLOT(on_buttonIasi5x3_clicked()));
	connect(Timisoara5x3, SIGNAL(clicked()), this, SLOT(on_buttonTimisoara5x3_clicked()));
	connect(Cluj5x3, SIGNAL(clicked()), this, SLOT(on_buttonCluj5x3_clicked()));
	connect(Transilvania5x3, SIGNAL(clicked()), this, SLOT(on_buttonTransilvania5x3_clicked()));
	connect(Brasov5x3, SIGNAL(clicked()), this, SLOT(on_buttonBrasov5x3_clicked()));
	connect(Galati5x3, SIGNAL(clicked()), this, SLOT(on_buttonGalati5x3_clicked()));
	connect(Banat5x3, SIGNAL(clicked()), this, SLOT(on_buttonBanat5x3_clicked()));
	connect(Oltenia5x3, SIGNAL(clicked()), this, SLOT(on_buttonOltenia5x3_clicked()));
	connect(Teleorman5x3, SIGNAL(clicked()), this, SLOT(on_buttonTeleorman5x3_clicked()));
	connect(Bucuresti5x3, SIGNAL(clicked()), this, SLOT(on_buttonBucuresti5x3_clicked()));
	connect(Calarasi5x3, SIGNAL(clicked()), this, SLOT(on_buttonCalarasi5x3_clicked()));
	connect(Tulcea5x3, SIGNAL(clicked()), this, SLOT(on_buttonTulcea5x3_clicked()));
	connect(Constanta5x3, SIGNAL(clicked()), this, SLOT(on_buttonConstanta5x3_clicked()));

	listButtons5x3.push_back(SatuMare5x3);
	listButtons5x3.push_back(Maramures5x3);
	listButtons5x3.push_back(Iasi5x3);
	listButtons5x3.push_back(Timisoara5x3);
	listButtons5x3.push_back(Cluj5x3);
	listButtons5x3.push_back(Transilvania5x3);
	listButtons5x3.push_back(Galati5x3);
	listButtons5x3.push_back(Banat5x3);
	listButtons5x3.push_back(Oltenia5x3);
	listButtons5x3.push_back(Teleorman5x3);
	listButtons5x3.push_back(Bucuresti5x3);
	listButtons5x3.push_back(Calarasi5x3);
	listButtons5x3.push_back(Tulcea5x3);
	listButtons5x3.push_back(Brasov5x3);
	listButtons5x3.push_back(Constanta5x3);

	this->SatuMare6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/SatuMare.png", this->ui.Game4Pers, 213, 20, 152, 117);
	this->Maramures6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Maramures.png", this->ui.Game4Pers, 347, 40, 112, 215);
	this->Suceava6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Suceava.png", this->ui.Game4Pers, 445, 22, 144, 127);
	this->Botosani6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Botosani.png", this->ui.Game4Pers, 529, 2, 156, 167);
	this->Bihor6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Bihor.png", this->ui.Game4Pers, 144, 65, 241, 184);
	this->Cluj26x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Cluj2.png", this->ui.Game4Pers, 155, 143, 152, 141);
	this->Cluj6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Cluj.png", this->ui.Game4Pers, 291, 83, 99, 155);
	this->Harghita6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Harghita.png", this->ui.Game4Pers, 379, 108, 184, 167);
	this->Iasi6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Iasi.png", this->ui.Game4Pers, 553, 112, 187, 121);
	this->Arad6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Arad.png", this->ui.Game4Pers, 6, 155, 181, 133);
	this->Banat6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Banat.png", this->ui.Game4Pers, 1, 275, 183, 185);
	this->Hunedoara6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Hunedoara.png", this->ui.Game4Pers, 165, 243, 142, 115);
	this->Alba6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Alba.png", this->ui.Game4Pers, 263, 239, 125, 117);
	this->Sibiu6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Sibiu.png", this->ui.Game4Pers, 336, 240, 142, 140);
	this->Brasov6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Brasov.png", this->ui.Game4Pers, 448, 227, 171, 153);
	this->Galati6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Vaslui.png", this->ui.Game4Pers, 561, 182, 196, 179);
	this->CarasSevarin6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/CaraSever.png", this->ui.Game4Pers, 100, 355, 157, 156);
	this->Mehedinti6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Mehedinti.png", this->ui.Game4Pers, 196, 353, 150, 252);
	this->Teleorman6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Teleorman.png", this->ui.Game4Pers, 291, 355, 172, 271);
	this->Bucuresti6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Bucuresti.png", this->ui.Game4Pers, 445, 357, 162, 279);
	this->Braila6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Braila.png", this->ui.Game4Pers, 585, 343, 154, 124);
	this->Calarasi6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Calarasi.png", this->ui.Game4Pers, 569, 458, 143, 123);
	this->Tulcea6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Tulcea.png", this->ui.Game4Pers, 707, 365, 192, 142);
	this->Constanta6x4 = createMaskedPushButton("100", ":/MainWindow/assets/6x4/Constanta.png", this->ui.Game4Pers, 662, 472, 155, 142);

	connect(SatuMare6x4, SIGNAL(clicked()), this, SLOT(on_buttonSatuMare6x4_clicked()));
	connect(Maramures6x4, SIGNAL(clicked()), this, SLOT(on_buttonMaramures6x4_clicked()));
	connect(Suceava6x4, SIGNAL(clicked()), this, SLOT(on_buttonSuceava6x4_clicked()));
	connect(Botosani6x4, SIGNAL(clicked()), this, SLOT(on_buttonBotosani6x4_clicked()));
	connect(Bihor6x4, SIGNAL(clicked()), this, SLOT(on_buttonBihor6x4_clicked()));
	connect(Cluj26x4, SIGNAL(clicked()), this, SLOT(on_buttonCluj26x4_clicked()));
	connect(Cluj6x4, SIGNAL(clicked()), this, SLOT(on_buttonCluj6x4_clicked()));
	connect(Harghita6x4, SIGNAL(clicked()), this, SLOT(on_buttonHarghita6x4_clicked()));
	connect(Iasi6x4, SIGNAL(clicked()), this, SLOT(on_buttonIasi6x4_clicked()));
	connect(Arad6x4, SIGNAL(clicked()), this, SLOT(on_buttonArad6x4_clicked()));
	connect(Banat6x4, SIGNAL(clicked()), this, SLOT(on_buttonBanat6x4_clicked()));
	connect(Hunedoara6x4, SIGNAL(clicked()), this, SLOT(on_buttonHunedoara6x4_clicked()));
	connect(Alba6x4, SIGNAL(clicked()), this, SLOT(on_buttonAlba6x4_clicked()));
	connect(Sibiu6x4, SIGNAL(clicked()), this, SLOT(on_buttonSibiu6x4_clicked()));
	connect(Brasov6x4, SIGNAL(clicked()), this, SLOT(on_buttonBrasov6x4_clicked()));
	connect(Galati6x4, SIGNAL(clicked()), this, SLOT(on_buttonGalati6x4_clicked()));
	connect(CarasSevarin6x4, SIGNAL(clicked()), this, SLOT(on_buttonCarasSevarin6x4_clicked()));
	connect(Mehedinti6x4, SIGNAL(clicked()), this, SLOT(on_buttonMehedinti6x4_clicked()));
	connect(Teleorman6x4, SIGNAL(clicked()), this, SLOT(on_buttonTeleorman6x4_clicked()));
	connect(Bucuresti6x4, SIGNAL(clicked()), this, SLOT(on_buttonBucuresti6x4_clicked()));
	connect(Braila6x4, SIGNAL(clicked()), this, SLOT(on_buttonBraila6x4_clicked()));
	connect(Calarasi6x4, SIGNAL(clicked()), this, SLOT(on_buttonCalarasi6x4_clicked()));
	connect(Tulcea6x4, SIGNAL(clicked()), this, SLOT(on_buttonTulcea6x4_clicked()));
	connect(Constanta6x4, SIGNAL(clicked()), this, SLOT(on_buttonConstanta6x4_clicked()));

	listButtons6x4.push_back(SatuMare6x4);
	listButtons6x4.push_back(Maramures6x4);
	listButtons6x4.push_back(Suceava6x4);
	listButtons6x4.push_back(Botosani6x4);
	listButtons6x4.push_back(Bihor6x4);
	listButtons6x4.push_back(Cluj26x4);
	listButtons6x4.push_back(Iasi6x4);
	listButtons6x4.push_back(Arad6x4);
	listButtons6x4.push_back(Harghita6x4);
	listButtons6x4.push_back(Banat6x4);
	listButtons6x4.push_back(Hunedoara6x4);
	listButtons6x4.push_back(Alba6x4);
	listButtons6x4.push_back(Sibiu6x4);
	listButtons6x4.push_back(Galati6x4);
	listButtons6x4.push_back(CarasSevarin6x4);
	listButtons6x4.push_back(Mehedinti6x4);
	listButtons6x4.push_back(Teleorman6x4);
	listButtons6x4.push_back(Bucuresti6x4);
	listButtons6x4.push_back(Braila6x4);
	listButtons6x4.push_back(Calarasi6x4);
	listButtons6x4.push_back(Tulcea6x4);
	listButtons6x4.push_back(Constanta6x4);
	listButtons6x4.push_back(Brasov6x4);
	listButtons6x4.push_back(Cluj6x4);
}

MainWindow::~MainWindow() {}

void MainWindow::on_radioButtonLoginShowPassword_released() {
	if (ui.radioButtonLoginShowPassword->isChecked() == true) {
		ui.lineEditLoginPassword->setEchoMode(QLineEdit::Normal);
	} else {
		ui.lineEditLoginPassword->setEchoMode(QLineEdit::Password);
	}
}

void MainWindow::on_radioButtonSignupShowPassword_released() {
	if (ui.radioButtonSignupShowPassword->isChecked() == true) {
		ui.lineEditSignupPassword->setEchoMode(QLineEdit::Normal);
	} else {
		ui.lineEditSignupPassword->setEchoMode(QLineEdit::Password);
	}
}

void MainWindow::on_buttonLobbyKickplayer1_clicked() {
	session.kickPlayer(2);
	ui.frameAvatar2->setVisible(false);
	ui.labelLobbyPlayername2->setVisible(false);
	ui.buttonLobbyKickplayer1->setVisible(false);
}

void MainWindow::on_buttonLobbyKickplayer2_clicked() {
	session.kickPlayer(3);
	ui.frameAvatar3->setVisible(false);
	ui.labelLobbyPlayername3->setVisible(false);
	ui.buttonLobbyKickplayer2->setVisible(false);
}

void MainWindow::on_buttonLobbyKickplayer3_clicked() {
	session.kickPlayer(4);
	ui.frameAvatar4->setVisible(false);
	ui.labelLobbyPlayername4->setVisible(false);
	ui.buttonLobbyKickplayer3->setVisible(false);
}

void MainWindow::on_buttonLobbyStart_clicked() {
	cpr::Response res = cpr::Post(
			cpr::Url("http://localhost:8080/match/start"),
			this->cookie_jar);

	this->cookie_jar = res.cookies;

	int n = generateRandomNumberNumber();
	auto question = intrebariNumere[n]["intrebare"].get<std::string>();
	auto ans = intrebariNumere[n]["raspuns"].get<std::string>();
	ans = intrebariNumere[n]["raspuns"].get<std::string>();
	ui.labelQuestionNumberQuestion->setText(question.c_str());
	ui.labelQuestionNumberAnswear->setText(ans.c_str());
	if (session.getNumberPlayer() < 2) {
		ui.Error->setVisible(true);
	} else {
		ui.stackedWidget->setCurrentIndex(6);
	}
	ConnectButton(session.getNumberPlayer());
	StartGame(session.getNumberPlayer());
}

void MainWindow::on_buttonLobbyLogout_clicked() {
	cpr::Response res = cpr::Post(
			cpr::Url("http://localhost:8080/lobby/delete"),
			this->cookie_jar);

	this->cookie_jar = res.cookies;

	if (res.status_code == 200) {
		ui.stackedWidget->setCurrentIndex(3);
	}
}

void MainWindow::setAllPoints() {
}

void MainWindow::on_buttonQuestionFiftyFifty_clicked() {
}

void MainWindow::on_buttonQuestionA_clicked() {
	ui.stackedWidget->setCurrentIndex(5 + session.getNumberPlayer());
}

void MainWindow::on_buttonQuestionB_clicked() {
	ui.stackedWidget->setCurrentIndex(5 + session.getNumberPlayer());
}

void MainWindow::on_buttonQuestionC_clicked() {
	ui.stackedWidget->setCurrentIndex(5 + session.getNumberPlayer());
}

void MainWindow::on_buttonQuestionD_clicked() {
	ui.stackedWidget->setCurrentIndex(5 + session.getNumberPlayer());
}

void MainWindow::on_buttonQuestionNumberEnter_clicked() {
	ui.stackedWidget->setCurrentIndex(5 + session.getNumberPlayer());
	ui.lineEditQuestionNumberInput->clear();
	if (session.getNumberPlayer() < 3) {
		ui.stackedWidget->setCurrentIndex(7);
	} else if (session.getNumberPlayer() < 4) {
		ui.stackedWidget->setCurrentIndex(8);
	} else if (session.getNumberPlayer() < 5) {
		ui.stackedWidget->setCurrentIndex(9);
	}
	user1.setMoves(2);
	ui.lcdNumberGame3x3Points1->display(user1.getPoints());
	ui.lcdNumberGame3x3Points2->display(user2.getPoints());
	ui.lcdNumberGame5x3Points1->display(user1.getPoints());
	ui.lcdNumberGame5x3Points2->display(user2.getPoints());
	ui.lcdNumberGame5x3Points3->display(user3.getPoints());
	ui.lcdNumberGame6x4Points1->display(user1.getPoints());
	ui.lcdNumberGame6x4Points2->display(user2.getPoints());
	ui.lcdNumberGame6x4Points3->display(user3.getPoints());
	ui.lcdNumberGame6x4Points4->display(user4.getPoints());
}

void MainWindow::changePassword() {
}

void MainWindow::VerifyPlayer() {
	ui.frameAvatar1->setVisible(true);
	ui.labelLobbyPlayername1->setVisible(true);
	QString name = user1.getUsername().c_str();
	ui.labelLobbyPlayername1->setText(name);
	name = user2.getUsername().c_str();
	ui.labelLobbyPlayername2->setText(name);
	if (session.getNumberPlayer() > 1 && session.isOnline(2)) {
		ui.frameAvatar2->setVisible(true);
		ui.buttonLobbyKickplayer1->setVisible(true);
		ui.labelLobbyPlayername2->setVisible(true);
		name = user2.getUsername().c_str();
		ui.labelLobbyPlayername2->setText(name);
	}
	if (session.getNumberPlayer() > 2 && session.isOnline(3)) {
		ui.frameAvatar3->setVisible(true);
		ui.buttonLobbyKickplayer2->setVisible(true);
		ui.labelLobbyPlayername3->setVisible(true);
		name = user3.getUsername().c_str();
		ui.labelLobbyPlayername3->setText(name);
	}
	if (session.getNumberPlayer() > 3 && session.isOnline(4)) {
		ui.frameAvatar4->setVisible(true);
		ui.buttonLobbyKickplayer3->setVisible(true);
		ui.labelLobbyPlayername4->setVisible(true);
		name = user4.getUsername().c_str();
		ui.labelLobbyPlayername4->setText(name);
	}
}

void MainWindow::ConnectButton(int nrPlayer) {

	if (nrPlayer == 2) {

	} else if (nrPlayer == 3) {

	} else if (nrPlayer == 4) {
	}
}

void MainWindow::on_buttonStartpageLogin_clicked() {
	ui.stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_buttonStartpageSignup_clicked() {
	ui.stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_buttonLoginBack_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonSignupBack_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_buttonLoginLogin_clicked() {
	std::string username = this->ui.lineEditLoginUsername->text().toStdString();
	std::string password = this->ui.lineEditLoginPassword->text().toStdString();

	nlohmann::json body_json = nlohmann::json::object();
	body_json["username"] = username;
	body_json["password"] = password;

	cpr::Response res = cpr::Post(
			cpr::Url("http://localhost:8080/users/login"),
			cpr::Body{body_json.dump()},
			cpr::Header{{"Content-Type", "application/json"}},
			this->cookie_jar);

	this->cookie_jar = res.cookies;

	if (res.status_code == 404) {
		// Incorrect credentials.
	} else if (res.status_code == 403 || res.status_code == 200) {
		ui.stackedWidget->setCurrentIndex(3);
		ui.radioButtonLoginShowPassword->setChecked(false);
		setAllPoints();
	}
}

void MainWindow::on_buttonSignupSignup_clicked() {
	std::string username = this->ui.lineEditSignupUsername->text().toStdString();
	std::string password = this->ui.lineEditSignupPassword->text().toStdString();

	nlohmann::json body_json = nlohmann::json::object();
	body_json["username"] = username;
	body_json["password"] = password;

	cpr::Response res = cpr::Post(
			cpr::Url("http://localhost:8080/users/register"),
			cpr::Body{body_json.dump()},
			cpr::Header{{"Content-Type", "application/json"}},
			this->cookie_jar);

	this->cookie_jar = res.cookies;

	if (res.status_code == 409) {
		// Already registered.
	} else if (res.status_code == 403 || res.status_code == 201) {
		ui.stackedWidget->setCurrentIndex(3);
		ui.radioButtonSignupShowPassword->setChecked(false);
		setAllPoints();
	}
}

void MainWindow::on_buttonMainMenuCreateGame_clicked() {
	cpr::Response res = cpr::Post(
			cpr::Url("http://localhost:8080/lobby/create"),
			this->cookie_jar);

	this->cookie_jar = res.cookies;

	if (res.status_code == 403) {
		// Not logged in
		ui.stackedWidget->setCurrentIndex(1);

	} else if (res.status_code == 500) {
		// Unexpected error
		ui.stackedWidget->setCurrentIndex(0);

	} else if (res.status_code == 201) {
		// Created
		ui.stackedWidget->setCurrentIndex(4);
		ui.frameAvatar2->setVisible(false);
		ui.frameAvatar3->setVisible(false);
		ui.frameAvatar4->setVisible(false);
		ui.buttonLobbyKickplayer1->setVisible(false);
		ui.buttonLobbyKickplayer2->setVisible(false);
		ui.buttonLobbyKickplayer3->setVisible(false);
		ui.labelLobbyPlayername2->setVisible(false);
		ui.labelLobbyPlayername3->setVisible(false);
		ui.labelLobbyPlayername4->setVisible(false);
		VerifyPlayer();
		ui.Error->setVisible(false);
	}
}

void MainWindow::on_buttonMainMenuJoinGame_clicked() {
	ui.stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_buttonSatuMare3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		SatuMare3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = SatuMare3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		SatuMare3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMoldova3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Moldova3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Moldova3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Moldova3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTimisoara3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Timisoara3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Timisoara3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Timisoara3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonArdeal3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Ardeal3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Ardeal3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Ardeal3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTransilvania3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Transilvania3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Transilvania3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Transilvania3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonOltenia3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Oltenia3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Oltenia3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Oltenia3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMuntenia3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Muntenia3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Muntenia3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Muntenia3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonDobrogea3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Dobrogea3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Dobrogea3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Dobrogea3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMaramures3x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Maramures3x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Maramures3x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		Maramures3x3->setDisabled(true);
		nrCounty3x3--;
		if (nrCounty3x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonSatuMare5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		SatuMare5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = SatuMare5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		SatuMare5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMaramures5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Maramures5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Maramures5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Maramures5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonIasi5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Iasi5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Iasi5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Iasi5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTimisoara5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Timisoara5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Timisoara5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Timisoara5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCluj5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Cluj5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Cluj5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Cluj5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTransilvania5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Transilvania5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Transilvania5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Transilvania5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBrasov5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Brasov5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Brasov5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Brasov5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonGalati5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Galati5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Galati5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Galati5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBanat5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Banat5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Banat5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Banat5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonOltenia5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Oltenia5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Oltenia5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Oltenia5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTeleorman5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Teleorman5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Teleorman5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Teleorman5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBucuresti5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Bucuresti5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Bucuresti5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Bucuresti5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCalarasi5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Calarasi5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Calarasi5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Calarasi5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTulcea5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Tulcea5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Tulcea5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Tulcea5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonConstanta5x3_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Constanta5x3->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Constanta5x3->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		Constanta5x3->setDisabled(true);
		nrCounty5x3--;
		if (nrCounty5x3 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonSatuMare6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		SatuMare6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = SatuMare6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		SatuMare6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMaramures6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Maramures6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Maramures6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Maramures6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonSuceava6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Suceava6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Suceava6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Suceava6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBotosani6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Botosani6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Botosani6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Botosani6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBihor6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Bihor6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Bihor6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Bihor6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCluj26x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Cluj26x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Cluj26x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Cluj26x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCluj6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Cluj6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Cluj6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Cluj6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonHarghita6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Harghita6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Harghita6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Harghita6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonIasi6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Iasi6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Iasi6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Iasi6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonArad6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Arad6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Arad6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Arad6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBanat6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Banat6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Banat6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Banat6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonHunedoara6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Hunedoara6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Hunedoara6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Hunedoara6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonAlba6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Alba6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Alba6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Alba6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonSibiu6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Sibiu6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Sibiu6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Sibiu6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBrasov6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Brasov6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Brasov6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Brasov6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonGalati6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Galati6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Galati6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Galati6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCarasSevarin6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		CarasSevarin6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = CarasSevarin6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		CarasSevarin6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonMehedinti6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Mehedinti6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Mehedinti6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Mehedinti6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTeleorman6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Teleorman6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Teleorman6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Teleorman6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBucuresti6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Bucuresti6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Bucuresti6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Bucuresti6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonBraila6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Braila6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Braila6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Braila6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonCalarasi6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Calarasi6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Calarasi6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Calarasi6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}
void MainWindow::on_buttonTulcea6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {

		Tulcea6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Tulcea6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Tulcea6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {

			enableButton();
			Round = true;
		}
	}
}

void MainWindow::on_buttonConstanta6x4_clicked() {
	if (Round == true) {
		getQuestionSimple();
		ui.stackedWidget->setCurrentIndex(5);
	} else {
		Constanta6x4->setStyleSheet("background-color:blue");
		AfterRegionSelect("a");
		getQuestionNumber();
		std::string nr = Constanta6x4->text().toStdString();
		user1.setPoints(addPoints(nr));
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		Constanta6x4->setDisabled(true);
		nrCounty6x4--;
		if (nrCounty6x4 == 0) {
			enableButton();
			Round = true;
		}
	}
}

void MainWindow::on_buttonHelp4Raspunsiri_clicked() {
	if (user1.getPoints() > 200) {
		user1.setPoints(user1.getPoints() - 100);
	}
}

void MainWindow::on_buttonHelpSugestie_clicked() {
	if (user1.getPoints() > 200) {
		user1.setPoints(user1.getPoints() - 100);
	}
}

void MainWindow::StartGame(int nrPlayer) {
	session.Verify(session.getNumberPlayer());
	QString name;
	if (nrPlayer == 2) {
		SatuMare3x3->setStyleSheet("background-color: red;");
		SatuMare3x3->setDisabled(true);
		Dobrogea3x3->setStyleSheet("background-color: blue;");
		Dobrogea3x3->setDisabled(true);
		name = session.getUser(1).c_str();
		ui.labelGame3x3Username1->setText(name);
		name = session.getUser(2).c_str();
		ui.labelGame3x3Username2->setText(name);
		ui.lcdNumberGame3x3Points1->display(user1.getPoints());
		ui.lcdNumberGame3x3Points2->display(user2.getPoints());
		user1.setColor(1);
		user2.setColor(2);
	} else if (nrPlayer == 3) {
		Iasi5x3->setStyleSheet("background-color: red;");
		Iasi5x3->setDisabled(true);
		Constanta5x3->setStyleSheet("background-color: blue;");
		Constanta5x3->setDisabled(true);
		Timisoara5x3->setStyleSheet("background-color: green;");
		Timisoara5x3->setDisabled(true);
		name = session.getUser(1).c_str();
		ui.labelGame5x3Username1->setText(name);
		name = session.getUser(2).c_str();
		ui.labelGame5x3Username2->setText(name);
		name = session.getUser(3).c_str();
		ui.labelGame5x3Username3->setText(name);
		ui.lcdNumberGame5x3Points1->display(user1.getPoints());
		ui.lcdNumberGame5x3Points2->display(user2.getPoints());
		ui.lcdNumberGame5x3Points3->display(user3.getPoints());
		user1.setColor(1);
		user2.setColor(2);
		user3.setColor(3);

	} else if (nrPlayer == 4) {
		user1.setMoves(2);
		SatuMare6x4->setStyleSheet("background-color: red;");
		SatuMare6x4->setDisabled(true);
		Constanta6x4->setStyleSheet("background-color: blue;");
		Constanta6x4->setDisabled(true);
		Iasi6x4->setStyleSheet("background-color: green;");
		Iasi6x4->setDisabled(true);
		CarasSevarin6x4->setStyleSheet("background-color: purple;");
		CarasSevarin6x4->setDisabled(true);
		name = session.getUser(1).c_str();
		ui.labelGame6x4Username1->setText(name);
		name = session.getUser(2).c_str();
		ui.labelGame6x4Username2->setText(name);
		name = session.getUser(3).c_str();
		ui.labelGame6x4Username3->setText(name);
		name = session.getUser(4).c_str();
		ui.labelGame6x4Username4->setText(name);
		ui.lcdNumberGame6x4Points1->display(user1.getPoints());
		ui.lcdNumberGame6x4Points2->display(user2.getPoints());
		ui.lcdNumberGame6x4Points3->display(user3.getPoints());
		ui.lcdNumberGame6x4Points4->display(user4.getPoints());
		user1.setColor(1);
		user2.setColor(2);
		user3.setColor(3);
		user4.setColor(4);
	}
}

void MainWindow::verify_ans(std::string ans) {
}

void MainWindow::AfterRegionSelect(const std::string &regionName) {
	user1.decreaseMove();
	if (user1.getMoves() == 0) {
		ui.stackedWidget->setCurrentIndex(6);
	}
}

int MainWindow::addPoints(std::string points) {
	int nr = std::stoi(points);
	nr = nr + user1.getPoints();
	return nr;
}

void MainWindow::enableButton() {
	SatuMare3x3->setEnabled(true);
	Moldova3x3->setEnabled(true);
	Timisoara3x3->setEnabled(true);
	Ardeal3x3->setEnabled(true);
	Transilvania3x3->setEnabled(true);
	Oltenia3x3->setEnabled(true);
	Muntenia3x3->setEnabled(true);
	Dobrogea3x3->setEnabled(true);
	Maramures3x3->setEnabled(true);
	SatuMare5x3->setEnabled(true);
	Maramures5x3->setEnabled(true);
	Iasi5x3->setEnabled(true);
	Timisoara5x3->setEnabled(true);
	Cluj5x3->setEnabled(true);
	Transilvania5x3->setEnabled(true);
	Brasov5x3->setEnabled(true);
	Galati5x3->setEnabled(true);
	Banat5x3->setEnabled(true);
	Oltenia5x3->setEnabled(true);
	Teleorman5x3->setEnabled(true);
	Bucuresti5x3->setEnabled(true);
	Calarasi5x3->setEnabled(true);
	Tulcea5x3->setEnabled(true);
	Constanta5x3->setEnabled(true);
	SatuMare6x4->setEnabled(true);
	Maramures6x4->setEnabled(true);
	Suceava6x4->setEnabled(true);
	Botosani6x4->setEnabled(true);
	Bihor6x4->setEnabled(true);
	Cluj26x4->setEnabled(true);
	Cluj6x4->setEnabled(true);
	Harghita6x4->setEnabled(true);
	Iasi6x4->setEnabled(true);
	Arad6x4->setEnabled(true);
	Banat6x4->setEnabled(true);
	Hunedoara6x4->setEnabled(true);
	Alba6x4->setEnabled(true);
	Sibiu6x4->setEnabled(true);
	Brasov6x4->setEnabled(true);
	Galati6x4->setEnabled(true);
	CarasSevarin6x4->setEnabled(true);
	Mehedinti6x4->setEnabled(true);
	Teleorman6x4->setEnabled(true);
	Bucuresti6x4->setEnabled(true);
	Braila6x4->setEnabled(true);
	Calarasi6x4->setEnabled(true);
	Tulcea6x4->setEnabled(true);
	Constanta6x4->setEnabled(true);
}

int MainWindow::generateRandomNumberNumber() {
	int n = this->distNumber(this->mt);
	if (this->randomNumbersNumberHistory.contains(n))
		return this->generateRandomNumberNumber();
	this->randomNumbersNumberHistory.emplace(n);
	return n;
}

int MainWindow::generateRandomSimpleNumber() {
	int n = this->distSimple(this->mt);
	if (this->randomNumbersSimpleHistory.contains(n))
		return this->generateRandomSimpleNumber();
	this->randomNumbersSimpleHistory.emplace(n);
	return n;
}

void MainWindow::getQuestionNumber() {
	int n;
	n = generateRandomNumberNumber();
	auto question = intrebariNumere[n]["intrebare"].get<std::string>();
	ui.labelQuestionNumberQuestion->setText(question.c_str());
	auto answer = intrebariNumere[n]["raspuns"].get<std::string>();
	ui.labelQuestionNumberAnswear->setText(answer.c_str());
}

void MainWindow::getQuestionSimple() {
	int n;
	n = generateRandomSimpleNumber();
	auto question = intrebariSimple[n]["intrebare"].get<std::string>();
	ui.labelQuestionQuestion->setText(question.c_str());

	auto answer1 = intrebariSimple[n]["raspunsuri"][0].get<std::string>();
	auto answer2 = intrebariSimple[n]["raspunsuri"][1].get<std::string>();
	auto answer3 = intrebariSimple[n]["raspunsuri"][2].get<std::string>();
	auto answer4 = intrebariSimple[n]["raspunsuri"][3].get<std::string>();
}
