#ifndef SRC_CLIENT_SVG_MANAGER_H
#define SRC_CLIENT_SVG_MANAGER_H

#include <QString>
#include <memory>
#include <QtSvg/QSvgRenderer>

class SvgManager {
public:
    std::shared_ptr<QSvgRenderer> GetSvgRenderer(QString texture_path);

private:
    std::map<QString, std::shared_ptr<QSvgRenderer>> cache_;
};

#endif // SRC_CLIENT_SVG_MANAGER_H
