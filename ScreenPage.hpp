#ifndef SCREENPAGE_HPP
#define SCREENPAGE_HPP

#include <QMap>
#include <QSet>
#include <QVariant>
#include <QVector>
#include <QWidget>

class MultPages;

/*!
 * \class ScreenPage
 * \brief The ScreenPage class Represents a single page inside \b{MultPages}
 * class
 */
class ScreenPage : public QWidget {
  Q_OBJECT
public:
  friend class MultPages;

  /*!
   * \brief Constructs a page
   */
  explicit ScreenPage(QWidget *parent = nullptr);

signals:

  /*!
   * \brief emmited when data is sent to page
   */
  void dataSent(ScreenPage *, const QVariant &);

  /*!
   * \brief emmited when data is recieved from a page
   */
  void dataRecieved(ScreenPage *, const QVariant &);

public:
  /*!
   * \brief Sends a data to specific page(Make sure the passed page has been
   * connected with this page) \param page The page where data will be sent
   * \param data The data to be sent
   * \return whether the operation has succeeded or not
   */
  bool sendTo(ScreenPage *page, const QVariant &data);

  /*!
   * \brief Check whether this page has a connection with a specific page
   */
  bool hasConnectionWith(ScreenPage *) const;

  /*!
   * \brief Get the page manager of this Page instance
   */
  MultPages *getParent() const;

  /*!
   * \brief FromPage Get the last loaded data from a specifi page
   */
  QVariant lastDataFromPage(ScreenPage *) const;

  /*!
   * \brief Get the last data recieved to this page
   */
  QVariant lastDataRecieved() const;

public slots:
  /*!
   * \brief End connection with a specific page
   * \param The page where connection must be end with
   */
  void endConnectionWith(ScreenPage *page);

private:
  QSet<ScreenPage *> connectedPages;
  QMap<ScreenPage *, QVariant> pagesRecievedFrom;
  QVariant lastData;
};

#endif // SCREENPAGE_HPP
