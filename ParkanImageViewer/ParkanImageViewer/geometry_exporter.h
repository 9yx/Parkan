#ifndef GEOMETRY_EXPORTER_H
#define GEOMETRY_EXPORTER_H

#include "interior_file.h"
#include "object_3d.h"
#include "files_filter.h"

#include <QString>
#include <QFileInfoList>

class GeometryExporter
{
public:

    enum class ExportFormat
    {
        Text,
        Obj,
        TexturedObj
    };

    bool export_geometry(const QString& i_from,
                         const QString& i_to) const;

    bool export_geometry(const QString& i_from,
                         const QString& i_to,
                         ExportFormat i_format) const;

    bool export_all_used_textures(const QFileInfoList& i_all_geometry_files, const QString& i_to) const;

    bool export_all_geometry_files(const QFileInfoList& i_all_geometry_files, const QDir& i_out_directory) const;

private:

    bool import_interior(const QString& i_from, InteriorFile& o_interior) const;
    bool import_3d_object(const QString& i_from, Object3d& o_object) const;
    bool export_as_text(const QString& i_from, const QString& i_to) const;
    bool export_as_obj(const QString& i_from, const QString& i_to) const;
    bool export_as_obj(const InteriorFile& i_interior, const QString& i_to) const;
    bool export_as_textured_obj(const QString& i_from, const QString& i_to) const;

    template<typename Model>
    bool export_geometry_as_textured_obj(const Model& i_model, const QString& i_to) const;

    ExportFormat auto_detect_format(const QString& i_file_name) const;
};

QFileInfoList get_geometry_files(const QString& i_dir);

#endif // GEOMETRY_EXPORTER_H