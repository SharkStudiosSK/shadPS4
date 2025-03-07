#pragma once

#include <memory>
#include <span>
#include <QDialog>
#include <QGroupBox>
#include <QPushButton>

#include "common/config.h"
#include "common/path_util.h"
#include "qt_gui/compatibility_info.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
    Q_OBJECT
public:
    explicit SettingsDialog(std::span<const QString> physical_devices,
                            std::shared_ptr<CompatibilityInfoClass> m_compat_info,
                            QWidget* parent = nullptr);
    ~SettingsDialog();

    bool eventFilter(QObject* obj, QEvent* event) override;
    void updateNoteTextEdit(const QString& groupName);

    int exec() override;

signals:
    void LanguageChanged(const std::string& locale);
    void CompatibilityChanged();

private:
    void LoadValuesFromConfig();
    void UpdateSettings();
    void ResetInstallFolders();
    void InitializeEmulatorLanguages();
    void OnLanguageChanged(int index);
    void OnCursorStateChanged(s16 index);

    std::unique_ptr<Ui::SettingsDialog> ui;

    std::map<std::string, int> languages;

    QString defaultTextEdit;

    int initialHeight;
};
