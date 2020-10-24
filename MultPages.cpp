#include "MultPages.hpp"

MultPages::MultPages(QWidget *parent) : QStackedWidget(parent) {}

void MultPages::addPage(ScreenPage *page, bool changeTo) {
  addWidget(page);
  page->setParent(this);
  if (changeTo) {
    setCurrentIndex(count() - 1);
  }
  emit pageAdded(count() - 1);
}

void MultPages::insertPage(ScreenPage *page, int index, bool changeTo) {
  insertWidget(index, page);
  if (changeTo) {
    setCurrentIndex(index);
  }
  emit pageAdded(index);
}

void MultPages::removePage(int index) {
  auto page = static_cast<ScreenPage *>(widget(index));
  emit toBeRemoved(page);
  removeWidget(page);
  delete page;
  emit pageRemoved(index);
}

void MultPages::removePage(ScreenPage *page) { removePage(indexOf(page)); }

ScreenPage *MultPages::pageAt(int index) {
  return static_cast<ScreenPage *>(widget(index));
}

void MultPages::toPage(int index) { setCurrentIndex(index); }

void MultPages::toPreviousPage() { toPage(currentIndex() - 1); }

void MultPages::toNextPage() { toPage(currentIndex() + 1); }

void MultPages::eraseFromTo(int first, int last) {
  const auto begin = first;
  for (; first <= last; ++first) {
    removePage(begin);
  }
}

void MultPages::removeCurrent() { removePage(currentIndex()); }

QVariant MultPages::lastDataFromPage(ScreenPage *page) {
  return page->lastData;
}

bool MultPages::connectPages(ScreenPage *sender, ScreenPage *reciever,
                             bool doubleConnection) {
  if (sender->connectedPages.contains(reciever) || reciever == sender) {
    return false;
  }
  sender->connectedPages.insert(reciever);
  if (doubleConnection) {
    connectPages(reciever, sender);
  }
  return true;
}

template <typename Func> ScreenPage *MultPages::getPageWhere(Func func) {
  for (auto i = 0; i < this->count(); ++i) {
    if (const auto page = pageAt(i); func(page)) {
      return page;
    }
  }
  return nullptr;
}
