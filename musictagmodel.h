#ifndef MUSICTAGMODEL_H
#define MUSICTAGMODEL_H
#include <QAbstractItemModel>
#include <QDir>


class MusicTagModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MusicTagModel(QObject* parent = nullptr);

    QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setDeviceRootPath(const QString &path);
    int appendScannedDirRelativePath(const QString &path);
    void setScannedDirRelativePath(const QStringList &path);

private slots:

private:
    QString deviceRootPath;
};

#endif // MUSICTAGMODEL_H
