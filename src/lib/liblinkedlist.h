/* linked list implementation that will allow storing multiple fields within
 * our struct */
struct node {
  void* value;
  struct node* next;
};
