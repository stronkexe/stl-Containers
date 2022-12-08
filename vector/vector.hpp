/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/08 17:10:13 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "../utils/exceptions.hpp"
#include "../utils/Iterator_traits.hpp"
#include "../utils/vector_Iterators.hpp"
#include "../utils/utils.hpp"
#include <cstddef>
// #include "reverse_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:
			typedef T							value_type;
			typedef Allocator					allocator_type;
			typedef	typename	allocator_type::pointer	pointer;
			typedef	typename	allocator_type::const_pointer	const_pointer;
			typedef	typename	allocator_type::reference	reference;
			typedef	typename	allocator_type::const_reference	const_reference;
			typedef	typename	allocator_type::difference_type	difference_type;
			// typedef T*							pointer;
			// typedef T&							reference;
			// typedef const T*					const_pointer;
			// typedef const T&					const_reference;
			typedef size_t						size_type;
			// typedef ptrdiff_t					difference_type;
			typedef ft::Iterator<T>					iterator;
			typedef ft::Iterator<const T >			const_iterator;
			typedef ft::Reverse_iterator<T>			reverse_iterator;
			typedef ft::Reverse_iterator<const T>	const_reverse_iterator;

		private:
			size_type		capcity;
			size_type		len;
			T				*v;
			allocator_type	_allocator;

		public:
			// >> Member functions
				//----	Constructors
					vector() : capcity(0), len(0), v(NULL)
					{
						// v = _allocator.allocate(len);
					};

					explicit vector( const Allocator& alloc ) : capcity(0), len(0), _allocator(alloc), v(NULL)
					{
						// v = _allocator.allocate(len);
						// std::cout << "vector default constractor called!" << std::endl;
					};

					explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : capcity(count), len(count), v(NULL), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						for (size_type i=0; i<len; i++)
							_allocator.construct(v+i, value);
					};

					template< class InputIt >
					vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = InputIt()) : v(NULL), _allocator(alloc)
					{
						size_type i=0,count=0;
						InputIt temp1=first, temp2=last;
					
						while (temp1 != temp2)
						{
							count+=1;
							temp1++;
						}
						len = count;
						capcity = len;
						v = _allocator.allocate(capcity);
						while (first != last)
						{
							_allocator.construct(v+i, *first);
							first++;
							i++;
						}
					};

					vector( const vector& other ) : capcity(other.capcity), len(other.len), v(NULL), _allocator(other._allocator)
					{
						size_type i=0;

						v = _allocator.allocate(len);
						while (i<len)
						{
							_allocator.construct(v+i, other.v[i]);
							i+=1;
						}
					};

				//----	Destructor
					~vector()
					{
						this->clear();
						std::cout << "vector Deconstractor called!" << std::endl;
					};

				//----	operator=
					vector& operator=( const vector& other )
					{
						if (*this != other)
						{
							for (size_type i=0; i<len; i++)
								_allocator.destroy(v+i);
							if (capcity)
								_allocator.deallocate(v, capcity);
							capcity = other.capcity;
							len = other.len;
							v = other.v;
							_allocator = other._allocator;
							for (size_type i=0; i<len; i++)
								_allocator.construct(v+i, other.v[i]);
						}
						return *this;
					};

				//---	assign
					void assign( size_type count, const T& value )
					{
						clear();
						if (count > capcity)
						{
							capcity = count;
							v = _allocator.allocate(capcity);
						}
						len = count;
						for (size_type i=0; i < len; i++)
							_allocator.construct(v+i, value);
					};
					template< class InputIt > void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = InputIt())
					{
						// int i=0;
						// for (iterator it=first; it != last; ++it)
						// 	v[i++] = it;
						size_type i=0;
						InputIt tempf, templ;

						tempf = first;
						templ = last;
						// std::cout << "holla\n";
						// while (tempf != templ)
						// {
						// 	i++;
						// }
						i = templ-tempf;
						clear();
						if (i > capcity)
						{
							capcity = i;
							v = _allocator.allocate(capcity);
						}
						len = capcity;
						i=0;
						// pointer tmp= _allocator.allocate(capcity);
						while (first != last)
						{
							// std::cout << "whota"<< i<<"\n";
							_allocator.construct(v+i, *first);
							first++;
							i++;
						}
						// v = tmp;
					};

				//----	get_allocator
					allocator_type get_allocator() const
					{
						return _allocator;
					};

				//----	Element access
					// at
						reference at( size_type pos )
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};
						const_reference at( size_type pos ) const
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};

					// operator[]
						reference operator[]( size_type pos )
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};
						const_reference operator[]( size_type pos ) const
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};

					// front
						reference front()
						{
							return v[0];
						};
						const_reference front() const
						{
							return v[0];
						};

					// back
						reference back()
						{
							return v[len-1];
						};
						const_reference back() const
						{
							return v[len-1];
						};

				//----	Iterators
					// begin
						iterator begin()
						{
							return iterator(v);
						};
						const_iterator begin() const
						{
							return const_iterator(v);
						};

					// end
						iterator end()
						{
							return iterator(v+len);
						};
						const_iterator end() const
						{
							return const_iterator( v+len);
						};

					// rbegin
						reverse_iterator rbegin()
						{
							return reverse_iterator(v);
						};
						const_reverse_iterator rbegin() const
						{
							return const_reverse_iterator(v);
						};

					// rend
						reverse_iterator rend()
						{
							return reverse_iterator(v+len);
						};
						const_reverse_iterator rend() const
						{
							return const_reverse_iterator( v+len);
						};

				//----	Capacity
					// empty
						bool empty() const
						{
							if (!len)
								return true;
							return false;
						};

					// size
						size_type size() const
						{
							return len;
						};

					// max_size
						size_type max_size() const
						{
							return _allocator.max_size();
						};

					// reserve
						void reserve( size_type new_cap )
						{
							size_type	temp_len;
							pointer		temp_v;
						
							if (new_cap > capcity)
							{
								temp_v = _allocator.allocate(new_cap);
								for (size_type i=0; i < len; i++)
									_allocator.construct(temp_v+i, v[i]);
								temp_len = len;
								clear();
								_allocator.deallocate(v, capcity);
								len = temp_len;
								v = temp_v;
								capcity = new_cap;
							}
						};

					// capacity
						size_type capacity() const
						{
							return capcity;
						};

				//----	Modifiers
					// clear
						void clear()
						{
							for (size_type i=0; i < capcity; i++)
								_allocator.destroy(v+i);
							len = 0;
						};

					// insert
						iterator insert( iterator pos, const T& value )
						{
							size_type index;
							value_type temp;

							index = &(*pos) - v;
							if (!capcity)
							{
								// capcity+=1;
								// len+=1;
								reserve(1);
							}
							else if (len+1 > capcity)
								capcity *= 2;
							// std::cout << v+len << "holla\n";
							_allocator.construct(v+len, value);
							for (size_type i=len; i > index; i--)
							{
								temp = v[i];
								v[i] = v[i-1];
								v[i-1] = temp;
							}
							len += 1;
							return iterator(v+index);
						};
						void insert( iterator pos, size_type count, const T& value )
						{
							size_type index;
							value_type temp;

							index = &(*pos) - v;
							if (len+count > capcity)
								capcity *= 2;
							for (size_type i=0; i < count; i++)
							{
								_allocator.construct(v+len, value);
								len += 1;
							}
							for (size_type x=0; x < count; x++)
							{
								for (size_type i=len-count+x; i > index; i--)
								{
									temp = v[i];
									v[i] = v[i-1];
									v[i-1] = temp;
								}
								index+=1;
							}
							// return iterator(v+index);
						};
						/*constexpr iterator  insert( const_iterator pos, size_type count, const T& value )
						{
							
						};
					*/	template< class InputIt > iterator insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
						{
							size_type index, count;
							value_type temp;
							InputIt tempf = first, templ = last;

							count = templ-tempf;
							index = &(*pos) - v;
							if (len+count > capcity)
								capcity *= 2;
							for (size_type i=0; i < count; i++)
							{
								_allocator.construct(v+len, *first++);
								len += 1;
							}
							for (size_type x=0; x < count; x++)
							{
								for (size_type i=len-count+x; i > index; i--)
								{
									temp = v[i];
									v[i] = v[i-1];
									v[i-1] = temp;
								}
								index+=1;
							}
						};

					// erase
						iterator erase( iterator pos )
						{
							size_type index;

							index = &(*pos) - v;
							_allocator.destroy(v+index);
							for (size_type i=index; i<len-1; i++)
								v[i] = v[i+1];
							len-=1;
							return iterator(v+index);
						};
						iterator erase( iterator first, iterator last )
						{
							size_type index, count, i;

							index = &(*first) - v;
							count = &(*last) - &(*first);
							for (i=index; i<count; i++)
								_allocator.destroy(v+i);
							for (size_type x=index; x<len; x++)
							{
								v[x] = v[x+count];
								i+=1;
							}
							len-=count;
							return iterator(v+index);
						};

					// push_back
						void push_back( const T& value )
						{
							if (!capcity)
								reserve(1);
							else if (len+1 > capcity)
								reserve(capcity * 2);
							_allocator.construct(v+len, value);
							len+=1;
						};

					// pop_back
						void pop_back()
						{
							_allocator.destroy(v+(len-1));
							len-=1;
						};

					// resize
						void resize( size_type count, T value = T() )
						{
							if (count < len)
							{
								for (size_type i=count; i<len; i++)
									_allocator.destroy(v+i);
								len = count;
							}
							else if (count <= capcity)
							{
								for (size_type i=len; i<count; i++)
									_allocator.construct(v+i, value);
								len += count;
							}
							else
							{
								// if (count > capcity*2)
									capcity = count;
								// else
								// 	capcity *= 2;
								pointer temp;
								temp = _allocator.allocate(capcity);
								for (size_type i=0; i<len; i++)
									_allocator.construct(temp+i, v[i]);
								for (size_type i=len; i<count; i++)
									_allocator.construct(temp+i, value);
								for (size_type i=0; i<len; i++)
									_allocator.destroy(v+i);
								v = temp;
								len = count;
							}
						};

					// swap
						void swap( vector& other )
						{
							int temp_len = len;
							T *temp_v = v;
							len = other.len;
							v = other.v;
							other.len = temp_len;
							other.v = temp_v;
						};

	};

	// >> Non-member functions
		//	operator==
			template< class T, class Alloc > bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			};

			//	operator!=
				template< class T, class Alloc > bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					return !(lhs == rhs);
				};

			//	operator<
				template< class T, class Alloc > bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				};

			//	operator<=
				template< class T, class Y, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return !(rhs < lhs);
				};

			//	operator>
				template< class T, class Y, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return rhs < lhs;
				};

			//	operator>=
				template< class T, class Alloc > bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
				{
					return !(lhs < rhs);
				};
}

#endif