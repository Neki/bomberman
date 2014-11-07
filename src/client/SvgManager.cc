#include "SvgManager.h"
#include <QCoreApplication>

std::shared_ptr<QSvgRenderer> SvgManager::GetSvgRenderer(QString texture_path) {
    if (!cache_[texture_path]) {
        cache_[texture_path] = std::make_shared<QSvgRenderer>(QCoreApplication::applicationDirPath() + "/" + texture_path);
    }

    return cache_[texture_path];
}
