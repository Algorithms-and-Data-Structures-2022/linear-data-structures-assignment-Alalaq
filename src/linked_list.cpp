#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* val = new Node(value);

    if (front_ == nullptr) {
      front_ = val;
      back_ = front_;
    }

    else{
      back_->next = val;
      back_ = val;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (size_ < index || index < 0){
      return false;
    }

    if (index == 0){
      front_ = new Node(value, front_);
      if (IsEmpty()){
        back_ = front_;
      }
      size_++;
      return true;
    }

    if (index == size_){
      Add(value);
      return true;
    }

    Node* node = front_;

    for (int i = 0; i < index - 1; i++){
      node = node->next;
    }


    Node* newNode = new Node(value, node->next);
    node->next = newNode;

    size_++;

    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (IsEmpty()){
      return false;
    }

    if (size_ <= index || index < 0){
      return false;
    }

    Node* node = front_;

    for (int i = 0; i < index; i++){
      node = node->next;
    }

    node->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (IsEmpty()){
      return std::nullopt;
    }

    if (size_ <= index || index < 0){
      return std::nullopt;
    }

    if(index == 0){
      Node* node = front_->next;
      int val = front_->value;

      delete front_;
      front_ = node;
      size_--;
      return val;
    }

    Node* prev = front_;

    for (int i = 0; i < index - 1; i++){
      prev = prev->next;
    }

    Node* node = prev->next;

    prev->next = node->next;
    int val = node->value;

    delete node;
    size_--;
    return val;
  }

  void LinkedList::Clear() {

    while (size_ > 0){
      Node *temp = front_;
      front_ = front_->next;

      delete temp;
      size_--;
    }
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (IsEmpty()){
      return std::nullopt;
    }

    if (size_ <= index || index < 0){
      return std::nullopt;
    }

    Node* node = front_;

    for (int i = 0; i < index; i++){
      node = node->next;
    }
    return node->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    if (IsEmpty()){
      return std::nullopt;
    }

    if (!Contains(value)){
      return std::nullopt;
    }

    Node* node = front_;

    for (int i = 0; i < size_; i++) {
      if (node->value == value) {
        return i;
      } else {
        node = node->next;
      }
    }
  }

  bool LinkedList::Contains(int value) const {
    if (IsEmpty()){
      return false;
    }

    Node* node = front_;

    for (int i = 0; i < size_; i++){
      if (node->value == value){
        return true;
      }
      else{
        node = node->next;
      }
    }

    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (front_ == nullptr) {
      return std::nullopt;
    }
    else{
      return front_->value;
    }
  }

  std::optional<int> LinkedList::back() const {
    if (back_ == nullptr) {
      return std::nullopt;
    }
    else{
      return back_->value;
    }
  }

  Node* LinkedList::FindNode(int index) const {
    if (IsEmpty()){
      return nullptr;
    }

    if (size_ <= index || index < 0){
      return nullptr;
    }

    Node* node = front_;

    for (int i = 0; i < index; i++){
      node = node->next;
    }
    return node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment