#pragma once

#include "i_view.h"

#include <QtWidgets/QMainWindow>
#include <QImage>


#include "opencv.hpp"
#include "../presenter/i_presenter.h"

#include "ui_MainWindow.h"

#include "ConfigWindow.h"

#include "../utils/qglobalshortcuts/qglobalshortcut.h"

class Presenter;

class WindowMain : public QMainWindow, IView, IRootView
{
	Q_OBJECT

public:
	WindowMain(QWidget *parent = 0);
	~WindowMain();
	IPresenter *presenter;
	void closeEvent(QCloseEvent* event) override;

	//Shortcuts
	QGlobalShortcut *toggle_tracking_shortcut{nullptr};

	//Iview stuff
	void connect_presenter(IPresenter* presenter);
	void paint_video_frame(cv::Mat& img);
	void show_tracking_data(ConfigData conf);
	ConfigData get_inputs();
	void update_view_state(ConfigData conf);
	void set_tracking_mode(bool is_tracking);
	void set_enabled(bool enabled);
	void show_message(const char* msg, MSG_SEVERITY severity);

	//IRootView
	void notify(IView *self);

private:
	Ui::MainWindow ui;
	QPushButton *btn_track, *btn_save, *btn_config;
	QLabel *tracking_frame, *tracking_info;
	//QGroupBox *gp_box_prefs, *gp_box_address, *gp_box_priors;
	QCheckBox *check_video_preview, *check_stabilization_landmarks, *check_enable_tracking_shortcut;
	//QComboBox* cb_modelType;

	ConfigWindow *conf_win;
	/**
	* Compacting the window to the content.
	*/
	void readjust_size();

	/**
	* Updates the view with the corresponding program state / config.
	*/
	void set_inputs(ConfigData data);


private slots:
	void onTrackClick();
	void onSaveClick();
	void onConfigClick();
	void onEnableTrackingShortcutClick();
};
