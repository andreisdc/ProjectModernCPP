#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
}

MainWindow::~MainWindow() {}

void MainWindow::on_radioButtonLoginShowPassword_released() {}

void MainWindow::on_radioButtonSignupShowPassword_released() {}

void MainWindow::on_buttonLobbyKickplayer1_clicked() {
}

void MainWindow::on_buttonLobbyKickplayer2_clicked() {
}

void MainWindow::on_buttonLobbyKickplayer3_clicked() {
}

void MainWindow::on_buttonLobbyAddplayer_clicked() {
	ui.stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_buttonLobbyStart_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_buttonWindowInviteAdd_clicked() {
	ui.stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_buttonLobbyLogout_clicked() {
	ui.stackedWidget->setCurrentIndex(0);
}

void MainWindow::setAllPoints() {

	ui.labelGameCountyPoints1->setText(initialPoints);
	ui.labelGameCountyPoints2->setText(initialPoints);
	ui.labelGameCountyPoints3->setText(initialPoints);
	ui.labelGameCountyPoints4->setText(initialPoints);
	ui.labelGameCountyPoints5->setText(initialPoints);
	ui.labelGameCountyPoints6->setText(initialPoints);
	ui.labelGameCountyPoints7->setText(initialPoints);
	ui.labelGameCountyPoints8->setText(initialPoints);
	ui.labelGameCountyPoints9->setText(initialPoints);
	ui.labelGameCountyPoints10->setText(initialPoints);
	ui.labelGameCountyPoints11->setText(initialPoints);
	ui.labelGameCountyPoints12->setText(initialPoints);
	ui.labelGameCountyPoints13->setText(initialPoints);
	ui.labelGameCountyPoints14->setText(initialPoints);
	ui.labelGameCountyPoints15->setText(initialPoints);
}

void MainWindow::on_buttonGameCounty1_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty2_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty3_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty4_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty5_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty6_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty7_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty8_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty9_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty10_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty11_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty12_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty13_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty14_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonGameCounty15_clicked() {
	ui.stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_buttonQuestionA_clicked() {
	ui.stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_buttonQuestionB_clicked() {
	ui.stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_buttonQuestionC_clicked() {
	ui.stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_buttonQuestionD_clicked() {
	ui.stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_buttonQuestionNumberEnter_clicked() {
	ui.stackedWidget->setCurrentIndex(5);
	ui.lineEditQuestionNumberInput->clear();
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

	ui.stackedWidget->setCurrentIndex(3);
	setAllPoints();
}

void MainWindow::on_buttonSignupSignup_clicked() {
	ui.stackedWidget->setCurrentIndex(3);
	setAllPoints();
}
