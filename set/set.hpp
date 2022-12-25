#ifndef SET_HPP
#define SET_HPP

#include "../map/map.hpp"
#include "../map/RBtree.hpp"
#include "../utils/exceptions.hpp"
#include <iostream>

namespace ft
{
    template<class Key, class Compare = std::less<Key>, class Allocator = std::allocator<Key> > class set
	{
		public:
			typedef	Key											key_type;
			typedef	Key											value_type;
			// typedef	ft::pair<key_type, mapped_type>							value_type;
			typedef	size_t										size_type;
			typedef	ptrdiff_t									difference_type;
			typedef	Compare										key_compare;
            typedef	Compare										val_comp;
			typedef	Allocator									allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;

			typedef typename ft::RBtree<value_type, val_comp>::iterator				iterator;
			typedef typename ft::RBtree<value_type, val_comp>::const_iterator			const_iterator;
			typedef typename ft::RBtree<value_type, val_comp>::reverse_iterator		reverse_iterator;
			typedef typename ft::RBtree<value_type, val_comp>::const_reverse_iterator	const_reverse_iterator;


		private:
			allocator_type					_allocator;
			key_compare						_key_comp;
			val_comp						val_cmp;
			RBtree<value_type, val_comp>	rbt;
			// size_type		len;

		public:
			// >> Member functions
				//----	Constructors
					// map() : _allocator(), _key_comp() , val_comp(), rbt()
					// {
					// 	std::cout << "map default constractor called" << std::endl;
					// };
					// explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator)
					explicit set( const key_compare& comp=key_compare(), const allocator_type& alloc = allocator_type() ) : _allocator(alloc), _key_comp(comp) , val_cmp(comp), rbt(_allocator) {};
					
                    template< class InputIt > set( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp), val_cmp(comp), rbt(_allocator)
					{
						insert(first, last);
					};

					set( const set& other ) : _allocator(other._allocator), _key_comp(other._key_comp), val_cmp(other.val_cmp), rbt(other.rbt) {};

				//----	Destructor
					~set() { std::cout << "set destructor called" << std::endl;};

				//----	operator=
					set& operator=( const set& other )
					{
						if (*this != other)
						{
							_allocator = other._allocator;
							_key_comp = other._key_comp;
							val_cmp = other.val_cmp;
							rbt = other.rbt;
						}
						// std::cout << "map assignement operator called" << std::endl;
						return *this;
					};

				//----	get_allocator
					allocator_type get_allocator() const
					{
						return _allocator;
					};

				//----	Element access
					//	operator[]
						// T& operator[]( const Key& key )
						// {
						// 	// if (key<0 || key>len)
						// 	// 	throw invalidIndex();
						// 	// return m[key];
						// 	// if (key_exists(key))
						// 	// {
						// 	// 	for (iterator it=begin(); it != end(); it++)
						// 	// 		if (it.key == key)
						// 	// 			return it.val;
						// 	// }
						// 	// insert(key);
						// 	// return m[len].val;
						// 	// iterator it;
							
						// 	// it = find(key);
						// 	// if (it != end())
						// 	// 	insert(ft::make_pair(key, mapped_type()));
						// 	// it = find(key);
						// 	// return it.second;
						// 	iterator it = rbt.find(ft::make_pair(key, mapped_type()));

						// 	if (it == end())
						// 	{
						// 		// ft::pair<iterator, bool> n = insert(ft::make_pair(key, mapped_type()));
						// 		// return n.first._node->data.second;
						// 		insert(ft::make_pair(key, mapped_type()));
						// 		iterator gg = find(key);
						// 		return gg._node->data.second;
								
						// 	}
						// 	return it._node->data.second;
						// };

				//----	Iterators
					//	begin
						iterator begin()
						{
							return rbt.begin();
						};
						const_iterator begin() const
						{
							return rbt.begin();
						};

					//	end
						iterator end()
						{
							return rbt.end();
						};
						const_iterator end() const
						{
							return rbt.end();
						};

					//	rbegin
						reverse_iterator rbegin()
						{
							return rbt.rbegin();
						};
						const_reverse_iterator rbegin() const
						{
							return rbt.rbegin();
						};

					//	rend
						reverse_iterator rend()
						{
							return rbt.rend();
						};
						const_reverse_iterator rend() const
						{
							return rbt.rend();
						};

				//----	Capacity
					//	empty
						bool empty() const
						{
							return rbt.empty();
						};

					//	size
						size_type size() const
						{
							return rbt.size();
						};

					//	max_size
						size_type max_size() const
						{
							return rbt.max_size();
						};

				//----	Modifiers
					//	clear
						void clear()
						{
							return rbt.clear();
						};

					//	insert
						ft::pair<iterator, bool> insert( const value_type& value )
						{
							return rbt.insert(value);
						};

						iterator insert( iterator pos, const value_type& value )
						{
							return rbt.insert(pos, value);
						};

						template< class InputIt >void insert( InputIt first, InputIt last /*, typename_sh*tt*/)
						{
							return rbt.insert(first, last);
						};

					//	erase
						iterator erase( iterator pos )
						{
							return rbt.erase(pos);
						};

						iterator erase( iterator first, iterator last )
						{
							return rbt.erase(first, last);
						};

						size_type erase( const Key& key )
						{
							return rbt.erase(key);
						};

					//	swap
						void swap( set& other )
						{
							std::swap(_allocator, other._allocator);
							std::swap(_key_comp, other._key_comp);
							std::swap(val_cmp, other.val_cmp);
							rbt.swap(other.rbt);
						};

				//----	Lookup
					//	count
						size_type count( const Key& key ) const
						{
							iterator it = find(key);
							if (it != end())
								return 1;
							return 0;
						};

					//	find
						iterator find( const Key& key )
						{
							return rbt.find(key);
						};
						const_iterator find( const Key& key ) const
						{
							return rbt.find(key);
						};

					//	equal_range
						ft::pair<iterator,iterator> equal_range( const Key& key )
						{
							return rbt.equal_range(key);
						};
						ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
						{
							return rbt.equal_range(key);
						};

					//	lower_bound
						iterator lower_bound( const Key& key )
						{
							return rbt.lower_bound(key);
						};
						const_iterator lower_bound( const Key& key ) const
						{
							return rbt.lower_bound(key);
						};

					//	upper_bound
						iterator upper_bound( const Key& key )
						{
							return rbt.upper_bound(key);
						};
						const_iterator upper_bound( const Key& key ) const
						{
							return rbt.upper_bound(key);
						};

				//----	Observers
					//	key_comp
						key_compare key_comp() const
						{
							return key_comp;
						};

					//	value_comp
						set::val_comp value_comp() const
						{
							return val_cmp;
						};

			// >> Non-member functions
				//	operator==
				//	operator!=
				//	operator<
				//	operator<=
				//	operator>
				//	operator>=
	};

	// >> Non-member functions
		//	operator==
	/*		template< class Key, class T, class Compare, class Alloc > bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			};

			//	operator!=
				template< class Key, class T, class Compare, class Alloc > bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(lhs == rhs);
				};

			//	operator<
				template< class Key, class T, class Compare, class Alloc > bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				};

			//	operator<=
				template< class Key, class T, class Compare, class Alloc > bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(rhs < lhs);
				};

			//	operator>
				template< class Key, class T, class Compare, class Alloc > bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return rhs < lhs;
				};

			//	operator>=
				template< class Key, class T, class Compare, class Alloc > bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(lhs < rhs);
				};*/
}

#endif