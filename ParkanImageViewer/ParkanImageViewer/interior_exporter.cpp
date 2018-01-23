#include "interior_exporter.h"

#include <QFileInfo>

#include <set>
#include <fstream>


bool InteriorExporter::export_interior(const QString &i_from, const QString &i_to, InteriorExporter::ExportFormat i_format) const
{
    switch(i_format)
    {
    case ExportFormat::Text:
        return export_as_text(i_from, i_to);
    default:
        return false;
    }
}

bool InteriorExporter::export_all_used_textures(const QFileInfoList &i_all_interiors, const QString &i_to) const
{
    if(i_all_interiors.empty())
        return false;

    std::set<std::string> texture_names;

    for(const auto& interior_file : i_all_interiors)
    {
        const QString file_path = interior_file.absoluteFilePath();
        std::cout << "Parsing interior file " << file_path.toStdString() << std::endl;
        const auto old_size = texture_names.size();

        InteriorFile interior;
        if(!import_interior(file_path, interior))
        {
            std::cout << "Could not load interior" << std::endl;
            continue;
        }

        for(const auto& p : interior.vertical_polygons.vec)
        {
            texture_names.insert(p.texture.to_std_string());
        }
        for(const auto& p : interior.horizontal_polygons.vec)
        {
            texture_names.insert(p.texture.to_std_string());
        }

        const auto new_size = texture_names.size();
        std::cout << "Found " << new_size - old_size << " textures" << std::endl;
    }

    if(texture_names.empty())
        return false;

    std::ofstream out(i_to.toStdString());
    for(const auto& name : texture_names)
    {
        out << name << std::endl;
    }
    return true;
}

bool InteriorExporter::import_interior(const QString &i_from, InteriorFile& o_interior) const
{
    if(i_from.isEmpty())
        return false;

    std::ifstream file(i_from.toStdString(), std::ios::binary);
    InputBinaryStream bis(file);
    bis >> o_interior;
    return true;
}

bool InteriorExporter::export_as_text(const QString &i_from, const QString &i_to) const
{
    if(i_to.isEmpty())
        return false;

    InteriorFile interior;
    if(!import_interior(i_from, interior))
        return false;

    std::ofstream out_file(i_to.toStdString());
    out_file << interior;
    return true;
}
