/*
 * Copyright (C) 2019 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBSTD_PRIORITYQUEUE_H
#define __LIBSTD_PRIORITYQUEUE_H

#include "Types.h"
#include "Macros.h"
#include "Container.h"

template <class T, Size N> class Priorityqueue : public Container
{
  public:

    Priorityqueue()
    {
        clear();
    }

    bool push(const T & item)
    {
        if (m_count >= N)
        {
            return false;
        }

        m_array[m_head] = item;
        m_head++;
        m_count++;
        int j=m_head-1;
        while(j>0&&m_array[j]>m_array[j-1]){
        	T temp=m_array[j];
        	m_array[j]=m_array[j-1];
        	m_array[j-1]=temp;
        	j--;
        }

        return true;
    }

    T & pop()
    {
        uint idx = m_head-1;
        m_head--;
        m_count--;

        return m_array[idx];
    }
    T & top()
    {
        return m_array[m_head-1];
    }

    bool contains(const T & item) const
    {
        for (Size i = 0; i < m_count; i++)
        {
            if (m_array[i] == item)
                return true;
        }

        return false;
    }

    void clear()
    {
        m_head = 0;
        m_count = 0;
    }

    Size size() const
    {
        return N;
    }
    Size count() const
    {
    	return m_count;
    }
    
    bool empty() const
    {
	return m_count==0;    
    }

  private:

    /** The actual array where the data is stored. */
    T m_array[N];

    /** Head of the queue */
    uint m_head;

    /** Number of items in the queue */
    uint m_count;
};


#endif /* __LIBSTD_PRIORITYQUEUE_H */
