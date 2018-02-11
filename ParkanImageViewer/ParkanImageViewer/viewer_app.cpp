#include "viewer_app.h"
#include "ui_viewer_app.h"

#include "color_ramp_widget.h"
#include "texture_factory.h"
#include "interior_exporter.h"

#include <QDir>
#include <QFileInfoList>
#include <QFileDialog>
#include <QMessageBox>

ViewerApp::ViewerApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerApp),
    m_crw(nullptr),
    m_img(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Parkan Image Viewer");

    QStringList all_palettes = Palette::get_all_palettes();
    ui->select_palette_combo_box->addItems(all_palettes);
}

ViewerApp::~ViewerApp()
{
    delete ui;
}

void ViewerApp::on_select_palette_combo_box_activated(const QString& i_palette_name)
{
    const Palette palette = Palette::get_palette_by_name(i_palette_name);
    m_crw.reset(new ColorRampWidget(palette));
    if (m_img)
    {
        m_img->set_palette(m_crw->m_palette);
        ui->image_label->setPixmap(QPixmap::fromImage(m_img->image()));
    }
}

void ViewerApp::on_actionExit_triggered()
{
    close();
}

void ViewerApp::on_actionOpen_Image_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (file_name.isEmpty())
        return;

    if(!m_crw)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "No palette", "Please select palette first");
        mb->show();
        return;
    }

    m_img = TextureFactory::build_image(file_name);
    if (!m_img)
        return;

    m_img->set_palette(m_crw->m_palette);
    ui->image_label->setPixmap(QPixmap::fromImage(m_img->image()));
}

void ViewerApp::on_actionOpen_interior_triggered()
{
    const QString file_name = QFileDialog::getOpenFileName();
    if (file_name.isEmpty())
        return;

    const QString out_file_name = QFileDialog::getSaveFileName();
    if(out_file_name.isEmpty())
        return;

    std::cout << "Exporting from " << file_name.toStdString() << " to " << out_file_name.toStdString() << std::endl;
    InteriorExporter().export_interior(file_name, out_file_name);
}

void ViewerApp::on_actionExport_all_used_textures_triggered()
{
    const QString dir_name = QFileDialog::getExistingDirectory();
    if (dir_name.isEmpty())
        return;

    const QString out_file_name = QFileDialog::getSaveFileName();
    if(out_file_name.isEmpty())
        return;

    QDir interiors_folder(dir_name);
    interiors_folder.setNameFilters(QStringList() << "*.BIN");
    const QFileInfoList all_interiors = interiors_folder.entryInfoList();
    InteriorExporter().export_all_used_textures(all_interiors, out_file_name);
}

void ViewerApp::on_actionSave_image_triggered()
{
    if(!m_img)
    {
        auto* mb = new QMessageBox(QMessageBox::Warning, "No image", "Please open image first");
        mb->show();
        return;
    }
    const QString out_file_name = QFileDialog::getSaveFileName();
    if(out_file_name.isEmpty())
        return;

    m_img->save(out_file_name);
}

void ViewerApp::on_actionExport_all_interiors_triggered()
{
    const QString dir_name = QFileDialog::getExistingDirectory();
    if (dir_name.isEmpty())
        return;

    const QString out_directory = QFileDialog::getExistingDirectory();
    if(out_directory.isEmpty())
        return;

    QDir interiors_folder(dir_name);
    interiors_folder.setNameFilters(QStringList() << "*.BIN");
    const QFileInfoList all_interiors = interiors_folder.entryInfoList();
    InteriorExporter().export_all_interiors(all_interiors, QDir(out_directory));
}
