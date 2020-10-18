#include "ScreenPage.hpp"
#include "MultPages.hpp"
#include <QDebug>
ScreenPage::ScreenPage(QWidget *parent) : QWidget(parent) {
  auto p = qobject_cast<MultPages *>(parent);
  if (p != nullptr) {
    connect(p, SIGNAL(toBeRemoved(ScreenPage *)), this,
            SLOT(endConnectionWith(ScreenPage *)));
  }
}

bool ScreenPage::sendTo(ScreenPage *page, const QVariant &data) {
  if (page == nullptr || data.isNull() || !data.isValid()) {
    return false;
  }
  if (!this->connectedPages.contains(page)) {
    return false;
  }
  if (page->pagesRecievedFrom.contains(this)) {
    page->pagesRecievedFrom[this] = data;
  } else {
    page->pagesRecievedFrom.insert(this, data);
  }
  emit dataSent(page, data);
  emit page->dataRecieved(this, data);
  lastData = data;
  return true;
}

MultPages *ScreenPage::getParent() const {
  return qobject_cast<MultPages *>(parent());
}

QVariant ScreenPage::lastDataRecieved() const { return lastData; }

QVariant ScreenPage::lastDataFromPage(ScreenPage *page) const {
  return hasConnectionWith(page) ? pagesRecievedFrom[page] : QVariant();
}

bool ScreenPage::hasConnectionWith(ScreenPage *page) const {
  return connectedPages.contains(page);
}

void ScreenPage::endConnectionWith(ScreenPage *page) {
  if (connectedPages.contains(page)) {
    connectedPages.remove(page);
  }
  if (pagesRecievedFrom.contains(page)) {
    pagesRecievedFrom.remove(page);
  }
}
