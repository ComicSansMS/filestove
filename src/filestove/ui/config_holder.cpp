#include <filestove/ui/config_holder.hpp>

#pragma warning(push)
#pragma warning(disable: 5054)
#include <QMessageBox>
#pragma warning(pop)

namespace filestove::ui
{

ConfigHolder::ConfigHolder(Config config)
    :m_config(std::move(config))
{
    connect(this, &ConfigHolder::configChanged, this,
            &ConfigHolder::saveConfig, Qt::QueuedConnection);
}

void ConfigHolder::saveConfig()
{
    try {
        writeConfig(m_config);
    } catch (std::exception& e) {
        QMessageBox msgbox;
        msgbox.setText("Error while saving config file");
        msgbox.setDetailedText(e.what());
        msgbox.exec();
    }
}

void ConfigHolder::updatePathlist(QStringList const& l)
{
    m_config.directories.clear();
    for (auto const& s : l) {
        m_config.directories.emplace_back(s.toStdString());
    }
    emit configChanged();
}

}
