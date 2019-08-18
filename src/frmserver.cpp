#include "frmserver.h"
#include "ui_frmserver.h"

FrmServer::FrmServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FrmServer)
{
    ui->setupUi(this);
    std::string public_ip = Connectivity::getPublicIp();
    ui->lblIpServer2->setText(QString::fromStdString(public_ip));
    ui->txtIpClient->setText("127.0.0.1");
    ui->txtPort->setText("49152");
    setFixedSize(size());

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()- static_cast<int>(width()*0.5),center.y()- static_cast<int>(height()*0.5));

    // Set icons

    setWindowIcon(QIcon(":/resources/media/mst_logo.png"));

    QPixmap back_img(":/resources/media/back.png");
    QIcon BackIcon(back_img);
    ui->btnBack->setIcon(BackIcon);
    ui->btnBack->setIconSize(back_img.rect().size());

    QPixmap load_img(":/resources/media/load.png");
    QIcon LoadIcon(load_img);
    ui->btnLoadConfig->setIcon(LoadIcon);
    ui->btnLoadConfig->setIconSize(load_img.rect().size());

    QPixmap save_img(":/resources/media/save.png");
    QIcon SaveIcon(save_img);
    ui->btnSaveConfig->setIcon(SaveIcon);
    ui->btnSaveConfig->setIconSize(save_img.rect().size());

    QPixmap start_img(":/resources/media/start.png");
    QIcon StartIcon(start_img);
    ui->btnStartServer->setIcon(StartIcon);
    ui->btnStartServer->setIconSize(start_img.rect().size());
}

FrmServer::~FrmServer()
{
    if(*selector == 1)
        *selector = -1;
    delete ui;
}

void FrmServer::setDict(Dictionary* dict)
{
    this->dict = dict;
    ui->lblInfoServer->setText(QString::fromStdString((*dict).getTextOflblInfoServer()));
    (*dict).setTextOflblIpServerS(ui->lblIpServer);
    (*dict).setTextOflblIpClientS(ui->lblIpClient);
    (*dict).setTextOflblPort(ui->lblPort);
    (*dict).setTextOflblPasswordS(ui->lblPassword);
    (*dict).setTextOflblSource(ui->lblSource);
    ui->lblConfig->setText(QString::fromStdString((*dict).getTextOflblConfig()));
    ui->lblLeaveConfig->setText(QString::fromStdString((*dict).getTextOflblLeaveConfig()));
    (*dict).setTextOflblResolution(ui->lblResolution);
    (*dict).setTextOflblFps(ui->lblFps);
    (*dict).setTextOflblBuffer(ui->lblBuffer);
    (*dict).setTextOflblVideo(ui->lblVideo);
    (*dict).setTextOflblColorScale(ui->lblColorScale);
    (*dict).setTextOflblEncoding(ui->lblEncoding);
    (*dict).setTextOflblAudio(ui->lblAudio);
    (*dict).setTextOflblControls(ui->lblControls);
    ui->lblBandwidth->setText(QString::fromStdString((*dict).getTextOflblBandwidth()));
    ui->lblBandwidthvalue->setText(QString::fromStdString((*dict).getTextOflblBandwidthvalue()));
    ui->btnBack->setText(QString::fromStdString((*dict).getTextOfbtnBack()));
    ui->btnLoadConfig->setText(QString::fromStdString((*dict).getTextOfbtnLoadConfig()));
    ui->btnSaveConfig->setText(QString::fromStdString((*dict).getTextOfbtnSaveConfig()));
    ui->btnStartServer->setText(QString::fromStdString((*dict).getTextOfbtnStartServer()));
    (*dict).fillcmbSource(ui->cmbSource);
    (*dict).fillcmbResolution(ui->cmbResolution);
    (*dict).fillcmbColorScale(ui->cmbColorScale);
    (*dict).fillcmbFps(ui->cmbFps);
    (*dict).fillcmbBuffer(ui->cmbBuffer);
    (*dict).fillcmbControls(ui->cmbControls);
}

void FrmServer::setSelector(int *selector)
{
    this->selector = selector;
}
void FrmServer::on_btnBack_clicked()
{
    *selector = 0;
    this->close();
}

void FrmServer::setConfigurations()
{
    Configurations::system = SERVER;
    Configurations::source = static_cast<uint8_t>(ui->cmbSource->currentIndex());
    Configurations::server_ip = ui->lblIpServer2->text().toStdString();
    Configurations::client_ip = ui->txtIpClient->text().toStdString();
    Configurations::port = static_cast<uint16_t>(stoi(ui->txtPort->text().toStdString()));
    Configurations::password = ui->txtPassword->text().toStdString();
    Configurations::leave_client_config = ui->chkLeaveConfig->isChecked();
    Configurations::resolution = static_cast<uint8_t>(ui->cmbResolution->currentIndex());
    Configurations::fps = static_cast<uint8_t>(ui->cmbFps->currentIndex());
    Configurations::buffer = static_cast<uint8_t>(ui->cmbBuffer->currentIndex());
    Configurations::color_scale = static_cast<uint8_t>(ui->cmbColorScale->currentIndex());
    Configurations::controls = static_cast<uint8_t>(ui->cmbControls->currentIndex());
    Configurations::file_name = "";
}

void FrmServer::on_btnStartServer_clicked()
{
    bool go_on = true;
    ui->btnStartServer->setEnabled(false);
    ui->btnStartServer->repaint();
    setConfigurations();
    if(Configurations::source_choices[Configurations::source] == "Video file")
    {
        Configurations::file_name = QFileDialog::getOpenFileName(this, QString::fromStdString((*dict).getTextOpenafile()),
                                                         QDir::homePath(), "*.mkv").toStdString();
        if(Configurations::file_name == "")
        {
            go_on = false;
            ui->btnStartServer->setEnabled(true);
        }
    }

    if(go_on)
    {
        *selector = 3;
        this->close();
    }
}