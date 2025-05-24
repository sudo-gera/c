use std::fmt::Debug;
use std::mem::swap;
use std::rc::Weak;
use std::cell::RefCell;
use std::rc::Rc;

struct ListNode<T>{
    next:   Option<Rc<RefCell<ListNode<T>>>>,
    prev: Option<Weak<RefCell<ListNode<T>>>>,
    value: Rc<RefCell<T>>,
}

#[derive(Debug)]
pub struct ListIter<T>{
    node: Weak<RefCell<ListNode<T>>>,
}

impl<T> ListIter<T>{
    pub fn next(&self) -> ListIter<T>{
        let node = self.node.upgrade().unwrap();
        ListIter::<T>{
            node: Rc::<RefCell<ListNode<T> > >::downgrade(node.borrow_mut().next.as_ref().unwrap()),
        }
    }

    pub fn prev(&self) -> ListIter<T>{
        let node = self.node.upgrade().unwrap();
        ListIter::<T>{
            node: node.borrow_mut().prev.as_ref().unwrap().clone(),
        }
    }

    pub fn value_rcrc(&self) -> Rc<RefCell<T>>{
        let node = self.node.upgrade().unwrap();
        node.borrow_mut().value.clone()
    }
}

impl<T> PartialEq for ListIter<T>{
    fn eq(&self, other: &Self) -> bool{
        Weak::ptr_eq(&self.node, &other.node)
    }
}

impl<T> Eq for ListIter<T>{}

impl<T> Clone for ListIter<T> {
    fn clone(&self) -> Self {
        Self{
            node: self.node.clone(),
        }
    }
}

pub struct DoubleLinkedList<T>{
    first:  Option<Rc<RefCell<ListNode<T>>>>,
    last: Option<Weak<RefCell<ListNode<T>>>>,
}

impl<T> Default for DoubleLinkedList<T> {
    fn default() -> Self {
        Self::new()
    }
}

impl<T> DoubleLinkedList<T>{
    pub fn first_iter(&mut self) -> ListIter<T>{
        ListIter::<T>{
            node: Rc::<RefCell<ListNode<T>>>::downgrade(&self.first.clone().unwrap())
        }
    }
    pub fn last_iter(&mut self) -> ListIter<T>{
        ListIter::<T>{
            node: self.last.clone().unwrap().clone()
        }
    }
    pub fn new() -> Self{
        Self{
            first: None,
            last:  None,
        }
    }
    pub fn from_one_item(value: T) -> Self{
        let value_ptr = Rc::new(
            RefCell::new(
                ListNode::<T>{
                    value: Rc::new(
                        RefCell::new(
                            value
                        )
                    ),
                    next: None,
                    prev: None,
                }
            )
        );
        Self{
            first: Some(value_ptr.clone()),
            last:  Some(Rc::<RefCell<ListNode<T> > >::downgrade(&value_ptr)),
        }
    }
    pub fn empty(&self) -> bool{
        self.first.is_none()
    }
    pub fn concat_by_stealing_from(&mut self, other: &mut Self){
        if self.empty(){
            swap(self, other);
            return
        }
        if other.empty(){
            return
        }

        let self_last = self.last_iter().node.upgrade().unwrap();
        let other_first = other.first_iter().node.upgrade().unwrap();
        
        let mut self_last_binding = self_last.borrow_mut();
        self_last_binding.next = Some(other_first.clone());
        drop(self_last_binding);

        let mut other_first_binding = other_first.borrow_mut();
        other_first_binding.prev = Some(std::rc::Rc::<RefCell<ListNode<T>>>::downgrade(&self_last));
        drop(other_first_binding);

        self.last = other.last.clone();

        other.first = None;
        other.last = None;
    }

    pub fn cut_starting_at(&mut self, iter: ListIter<T>) -> Self{
        let mut new_list = Self::new();
        let new_start = iter.node.upgrade().unwrap();
        let new_start_binding = new_start.borrow_mut();
        if new_start_binding.prev.is_none(){
            swap(&mut new_list, self);
            return new_list;
        }
        let new_end = new_start_binding.prev.as_ref().unwrap().clone();
        drop(new_start_binding);
        new_list.first = Some(new_start);
        new_list.last = self.last.clone();
        self.last = Some(new_end);
        new_list
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    pub fn check<T: Debug>(list: &mut DoubleLinkedList<T>, size: Option<usize>){
        if list.empty(){
            assert!(list.first.is_none());
            assert!(list.last.is_none());
            return;
        }else{
            assert!(list.first.is_some());
            assert!(list.last.is_some());
        }
        let mut iters = vec![list.first_iter()];
        loop{
            let to_push = iters.len() - 1;
            let to_push = iters[to_push].clone();
            if to_push == list.last_iter(){
                break;
            }
            let to_push = to_push.next().clone();
            iters.push(to_push.clone());
        }
        for i in 0..iters.len() {
            assert_eq!(iters[i], iters[i]);
        }
        for i in 1..iters.len() {
            assert_eq!(iters[i].prev(), iters[i-1]);
            assert_eq!(iters[i], iters[i-1].next());
        }
        assert_eq!(iters[0], list.first_iter());
        assert_eq!(iters[iters.len() - 1], list.last_iter());
        if size.is_some(){
            assert_eq!(size.unwrap(), iters.len());
        }
    }

    #[test]
    fn it_works() {
        let mut a = DoubleLinkedList::<Vec<i32>>::new();

        check(&mut a, Some(0));

        let mut s = DoubleLinkedList::<Vec<i32>>::from_one_item(vec![0]);

        check(&mut s, Some(1));

        a.concat_by_stealing_from(&mut s);

        check(&mut s, Some(0));
        check(&mut a, Some(1));

        let mut s = DoubleLinkedList::<Vec<i32>>::from_one_item(vec![0]);

        check(&mut s, Some(1));

        a.concat_by_stealing_from(&mut s);

        check(&mut s, Some(0));
        check(&mut a, Some(2));

        let mut s = DoubleLinkedList::<Vec<i32>>::from_one_item(vec![0]);

        check(&mut s, Some(1));

        a.concat_by_stealing_from(&mut s);

        check(&mut s, Some(0));
        check(&mut a, Some(3));

        let mut d = DoubleLinkedList::<Vec<i32>>::from_one_item(vec![0]);

        check(&mut d, Some(1));

        let mut s = DoubleLinkedList::<Vec<i32>>::from_one_item(vec![0]);

        check(&mut s, Some(1));

        d.concat_by_stealing_from(&mut s);

        check(&mut s, Some(0));
        check(&mut d, Some(2));

        a.concat_by_stealing_from(&mut d);

        check(&mut a, Some(5));
        check(&mut d, Some(0));

        let a2i = a.first_iter().next().next();
        let mut s = a.cut_starting_at(a2i);

        check(&mut a, Some(2));
        check(&mut s, Some(3));
    }
}
