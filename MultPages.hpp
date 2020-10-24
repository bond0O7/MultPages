#ifndef MULTPAGES_HPP
#define MULTPAGES_HPP
#include "ScreenPage.hpp"
#include <QStackedWidget>

/*!
 *\class MutlPages
 * \brief The MultPages class provides the functionality to manage pages(Using
 *\b {ScreenPage} class)
 */
class MultPages : public QStackedWidget {
  Q_OBJECT
public:
  /*!
   * \brief MultPages Constructs an instance of MultPages
   */
  explicit MultPages(QWidget *parent = nullptr);

public slots:
  /*!
   * \brief addPage Append a page at the end
   * \param changeTo Whether to switch the newly created page or not, set false
   * by default
   */
  void addPage(ScreenPage *, bool changeTo = false);

  /*!
   * \brief insertPage Insert a page in a specific index
   * \param changeTo Whether to switch to the newly created page or not, set
   * false by default
   */
  void insertPage(ScreenPage *, int, bool changeTo = false);

  /*!
   * \brief removePage remove a page at a specific given index
   */
  void removePage(int);

  /*!
   * \brief removePage Remove a specified page
   */
  void removePage(ScreenPage *);

  /*!
   * \brief pageAt Gets a pointer to the page at a specific index
   */
  ScreenPage *pageAt(int);

  /*!
   * \brief toPage Switch to a page at specific index
   */
  void toPage(int);

  /*!
   * \brief toPreviousPage Switch to the previous page
   */
  void toPreviousPage();

  /*!
   * \brief toNextPage Switch to the next page
   */
  void toNextPage();

  /*!
   * \brief eraseFromTo Remove pages between two indexes(both inclusively)
   */
  void eraseFromTo(int, int);

  /*!
   * \brief removeCurrent Remove the current Page
   */
  void removeCurrent();

public:
  /*!
   *\brief getPageWhere return a page pointer where it meets the condition
   */
  template <typename Func> ScreenPage *getPageWhere(Func func);

  QVariant lastDataFromPage(ScreenPage *);

public:
  bool static connectPages(ScreenPage *, ScreenPage *, bool = false);

signals:
  void pageAdded(int);
  void pageRemoved(int);
  void toBeRemoved(ScreenPage *);
};

#endif // MULTPAGES_HPP
