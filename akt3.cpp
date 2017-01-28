#ifndef __PROGTEST__
#include <iostream>
#include <sstream>
#include <vector>
#include <exception>

using namespace std;

class CIndexException
{
                  int row;
           public:
                CIndexException(int row): row(row) {}
                friend ostream& operator<<(ostream& os, const CIndexException & e );
};

ostream & operator << ( ostream & os, const CIndexException & e )
{
         os << "chyba: " << e.row << endl;
         return os;
}

struct t_edge
{
        int sourceIndex;
        int destinationIndex;
        int value;
        t_edge() {}
        t_edge(const int s, const int d, const int v): sourceIndex(s), destinationIndex(d), value(v) {}
};
 
struct t_node
{
        int status;
};
 
class CGraph
{
                vector< t_node * >         nd;
                vector< t_edge * >        edg;
        public:    
                bool            isOG (  ) const { return true; }
                                CGraph ( const int i );
                                ~CGraph();
                int             getEdgeCounter (  ) const { return edg.size() ; }
                t_edge  &       getEdge ( const int index ) const;
                void            setEdge ( const int index, const t_edge & edge );
                void            addEdge ( const t_edge & edge );
                void            deleteEdge ( const int index );
                int             getNodeCounter (  ) const { return nd.size(); }
                t_node  &       getNode ( const int index ) const;
                void            setNode ( const int index, const t_node & node );
};

CGraph::CGraph(const int i )
{
        for ( int j=0; j<i; j++ )
                nd.push_back( new t_node );
}

CGraph::~CGraph()
{
        for ( vector< t_edge * >::iterator it = edg.begin(); it != edg.end(); it ++ )
                delete *it ;
        for ( vector< t_node * >::iterator it = nd.begin(); it != nd.end(); it ++ )
                delete *it ;

}

t_edge & CGraph::getEdge( const int index ) const
{
        if ( (unsigned) index > edg.size() ) throw CIndexException(index);
        return * edg[index - 1 ];
}

void CGraph::deleteEdge ( const int index )
{
        delete edg[index - 1];
        edg.erase ( edg.begin() + index - 1 );
}

void CGraph::setEdge( const int index, const t_edge & edge )
{
        t_edge & tmp = * edg[index - 1];
        tmp.sourceIndex = edge.sourceIndex;
        tmp.destinationIndex = edge.destinationIndex;
        tmp.value = edge.value;
}

void CGraph::addEdge ( const t_edge & edge )
{
        t_edge * tmp = new t_edge;
        edg.push_back ( tmp );
        tmp -> sourceIndex = edge.sourceIndex;
        tmp -> destinationIndex = edge.destinationIndex;
        tmp -> value  = edge.value;
}

t_node & CGraph::getNode( const int index ) const
{
        if ( (unsigned) index > nd.size() ) throw CIndexException(index);
        return * nd[index - 1];
}


void CGraph::setNode ( const int index, const t_node & node )
{
        nd[index - 1] -> status = node.status;
}

#endif

template <typename T>
class CQueue
{
public:
                CQueue  () : head ( new Nod ) { bottom = head; }
                ~CQueue ();
        void    enQ     ( T item );
        T       deQ     ();
        size_t  listQ   ( T * out ) const;
        T       popQ    ();
        bool    isEmpty () const { return head == bottom; }
        bool    isInQ   ( T elem ) const;
        size_t  sizeQ() const;
private:
        struct Nod
        {
                Nod () : prev( nullptr ), next ( nullptr ) {}
                T record;
                Nod * prev, * next;
        };
        Nod * bottom, * head;
};

template< typename T >
class heap
{
        private:
                 T *     data;
                 bool    isMin;
                 size_t  arraySize;
                 size_t  dataSize;
                 void    extend();
                 void    shrink();
                 size_t  left  ( size_t index ) { return 2* index + 1; }
                 size_t  right ( size_t index ) { return 2* index + 2; }
                 size_t  parent( size_t index ) { return (index-1)/2; }
                 void    bubbleUp( size_t index );
                 void    bubbleDown( size_t index );
        public:
                        heap( bool isMin = true );
                        ~heap() { delete [] data; }
                 void   insert( const T & item );
                 T      pop();
                 T      get() const;
                 bool   isEmpty() const { return dataSize == 0; }
                 void   printArray () const { for (size_t i=0; i<dataSize; i++) cout << data[i] << ", "; }
};

struct edg_val
{
        t_edge e;
        edg_val() {}
        edg_val( const t_edge & ee ) : e(ee) {}
        bool operator < ( const edg_val & ee ) { return e.value <  ee.e.value; }
        bool operator <=( const edg_val & ee ) { return e.value <= ee.e.value; }
        bool operator >=( const edg_val & ee ) { return e.value >= ee.e.value; }
        bool operator > ( const edg_val & ee ) { return e.value >  ee.e.value; }

};

void MST1 ( CGraph & g )
{
        CQueue< t_edge > * nbs;
        t_edge  *  buff;
        if ( g.isOG() )
        {
                nbs = new CQueue< t_edge > [ 2 * g.getNodeCounter() ];
                buff = new t_edge[ 2 * g.getNodeCounter() ];
        }
        else 
        {
                nbs = new CQueue< t_edge > [ g.getNodeCounter() ];
                buff = new t_edge[ g.getNodeCounter() ];
        }
        int buffLen;

        for ( int i = g.getEdgeCounter(); i>0; i-- )
        {
                t_edge & tmpe = g.getEdge(i);
                nbs[ tmpe.sourceIndex - 1 ] .enQ( tmpe );
                nbs[ tmpe.destinationIndex - 1 ] .enQ( tmpe );

        }
        for ( int i = g.getNodeCounter(); i>0; i-- )
                (g.getNode(i)).status = 0;


        heap< edg_val > horizont;
        CQueue< t_edge > path;

        CQueue< int > toDo;
        int     current;
        for ( int i=g.getNodeCounter(); i>0; i-- )
                toDo.enQ(i);

        while ( ! toDo.isEmpty() )
        {
                current = toDo.popQ();
                if ( (g.getNode(current)) . status != 0 ) continue;
        ////        cout << " going to: " << current << endl;
                (g.getNode(current)) . status = 1;
                buffLen = nbs[ current-1 ] . listQ( buff );
                int theOther;
                for ( int i=0; i<buffLen; i++)
                {
                        if ( (buff[i] . sourceIndex) == current )
                                theOther = buff[ i ] . destinationIndex;

                        else if ( (buff[i] . destinationIndex) == current )
                                theOther = buff[ i ] . sourceIndex;

                        if ( ( g.getNode( theOther ) . status ) == 0 )
                                horizont.insert( buff[ i ] );
                }

                while ( ! horizont.isEmpty() )
                {
                        t_edge tmpe = horizont.pop().e;
                        if ( (g.getNode(tmpe.sourceIndex)) . status == 0 )
                        {
                                toDo.enQ( tmpe.sourceIndex );
                                path.enQ( tmpe );
                                break;
                        }
                        else if (g.getNode(tmpe.destinationIndex) . status == 0 )
                        {
                                toDo.enQ( tmpe.destinationIndex );
                                path.enQ( tmpe );
                                break;
                        }
                }
        }

        const int pathL = (int) path.sizeQ();

        for ( int i = g.getEdgeCounter(); i > pathL; --i )
                g.deleteEdge( i );

        for ( int i = pathL; i>0; i-- )
        {
                t_edge tmpe = path.popQ();
                g.setEdge( i, tmpe );
                //cout << tmpe.sourceIndex << " --> " << tmpe.destinationIndex << " (" << tmpe.value << ")\n";
        }

        delete [] nbs;
        delete [] buff;
}

template< typename T >
void heap< T >::shrink()
{
        T* tmp = new T[arraySize/2];
        for ( size_t i=0; i<dataSize; i++ )
                tmp[i] = data[i];
        delete [] data;
        data = tmp;
        arraySize /= 2;
}

template< typename T >
void heap< T >::extend()
{
        T* tmp = new T[2*arraySize];
        for ( size_t i=0; i<dataSize; i++ )
                tmp[i] = data[i];
        delete [] data;
        data = tmp;
        arraySize *= 2;
}

template< typename T >
T heap< T >::pop()
{
        if (dataSize == 0 ) throw "HeapUnderflow\n";
        if ( ( dataSize > 128 ) && ( 4 * dataSize < arraySize ) )
                shrink();
        T output = data[0];
        dataSize--;
        data[0] = data[dataSize];
        bubbleDown( 0 );
        return output;
}

template< typename T >
void heap< T >::bubbleDown(size_t index)
{
        if ( isMin )
        {
                while ( left(index)  < dataSize )
                {
                        size_t tmp;
                        if ((size_t) right(index) == dataSize )
                                tmp = left(index);
                        else
                                tmp = ( data[ left(index) ] <= data[ right(index) ] ) ?
                                        left(index) : right(index);
                        if ( data[index] < data[tmp] )
                                break;
                        T tmpt = data[index];
                        data[ index ] = data[ tmp ];
                        data[ tmp ] = tmpt;
                        index = tmp;
                }

        }
        else
        {
                while ( left(index)  < dataSize )
                {
                        size_t tmp;
                        if ( (size_t) right(index) == dataSize )
                                tmp = left(index);
                        else
                                tmp = ( data[ left(index) ] <= data[ right(index) ] ) ?
                                        right(index) : left(index);
                        if ( data[index] > data[tmp] )
                                break;
                        T tmpt = data[index];
                        data[ index ] = data[ tmp ];
                        data[ tmp ] = tmpt;
                        index = tmp;
                }

        }
}

template< typename T >
void heap< T >::insert( const T & item )
{
        if ( dataSize == arraySize )
                extend();
        dataSize++;
        data[dataSize-1] = item;
        bubbleUp ( dataSize - 1 );
}

template< typename T >
void heap< T >::bubbleUp ( size_t index )
{
        if ( isMin )
        {
                while ( index != 0 )
                {
                        if ( data[index] > data[ parent(index) ] )
                                break;
                        T tmp = data[ (index-1) / 2 ];
                        data[ parent(index) ] = data[ index ];
                        data[ index ] = tmp;
                        index = parent(index); 
                }
        }
        else
        {
                while ( index != 0 )
                {
                //        cout << index << endl;
                        if ( data[index] < data[ parent(index) ] )
                                break;
                        T tmp = data[ (index-1) / 2 ];
                        data[ parent(index) ] = data[ index ];
                        data[ index ] = tmp;
                        index = parent(index); 
                }
        }
}

template< typename T >
heap< T >::heap( bool ismin ) : isMin( ismin ), arraySize(128), dataSize(0)
{
        data = new T[arraySize];
}



template <typename T>
T CQueue<T>::popQ()
{
        if ( head == bottom ) throw "Queue underflow\n";
        Nod * tmpN = head;
        head = head->prev;
        T tmp = head->record;
        delete tmpN;
        return tmp;
}

template <typename T>
CQueue<T>::~CQueue()
{
        while ( bottom != head ) deQ();
        delete head;
}

template <typename T>
void CQueue<T>::enQ( T item )
{
        Nod * tmpN = new Nod;
        tmpN -> prev = head;
        head -> next = tmpN;
        head -> record = item;
        head = tmpN;
}

template <typename T>
T CQueue<T>::deQ ()
{
        if ( head == bottom ) throw "Queue underflow\n";
        T tmpT = bottom->record;
        bottom = bottom->next;
        delete bottom -> prev;
        bottom->prev = nullptr;
        return tmpT;
}

template <typename T>
size_t CQueue<T>::listQ (T * out) const
{
        Nod * tmp = bottom;
        size_t len(0);
        while ( tmp != head )
        {
            out[len] = tmp->record;
            tmp = tmp->next;
            len ++ ;
        }
        return len;
}

template <typename T>
size_t CQueue<T>::sizeQ() const
{
        Nod * tmp = bottom;
        size_t len(0);
        while ( tmp != head )
        {
            tmp = tmp->next;
            len ++ ;
        }
        return len;
}

template <typename T>
bool CQueue<T>::isInQ ( T elem ) const
{
        Nod * tmp = head;
        while ( tmp != bottom )
        {
                tmp = tmp -> prev;
                if ( tmp -> record == elem )
                        return true;
        }
        return false;
}

#ifndef __PROGTEST__
int main()
{
        CGraph g( 13 );
        g.addEdge(t_edge( 1,13, 61));
        g.addEdge(t_edge( 2, 5, 5 ));
        g.addEdge(t_edge( 2, 6, 88));
        g.addEdge(t_edge( 3, 2, 48));
        g.addEdge(t_edge( 3, 7, 34));
        g.addEdge(t_edge( 3,13, 98));
        g.addEdge(t_edge( 4, 5, 1 ));
        g.addEdge(t_edge( 4, 7, 67));
        g.addEdge(t_edge( 4, 8, 79));
        g.addEdge(t_edge( 5, 2, 34));
        g.addEdge(t_edge( 5, 4, 54));
        g.addEdge(t_edge( 5, 6, 63));
        g.addEdge(t_edge( 5,10, 94));
        g.addEdge(t_edge( 6, 5, 42));
        g.addEdge(t_edge( 6, 8, 90));
        g.addEdge(t_edge( 7, 8, 48));
        g.addEdge(t_edge( 9, 2, 0 ));
        g.addEdge(t_edge( 9, 5, 29));
        g.addEdge(t_edge( 9, 7, 32));
        g.addEdge(t_edge( 9,13, 92));
        g.addEdge(t_edge(12, 2, 73));
        g.addEdge(t_edge(12, 6, 69));
        g.addEdge(t_edge(12, 7, 78));
        g.addEdge(t_edge(12,11, 37));
        g.addEdge(t_edge(13,11, 89));
        g.addEdge(t_edge(13,12, 20));

        MST1( g );

        for ( int i = g.getEdgeCounter(); i>0; i-- )
        {
                t_edge & tmpe = g.getEdge(i);
                cout << tmpe.sourceIndex << " --> " << tmpe.destinationIndex << " (" << tmpe.value << ")\n";
        }

        return 0;
}
#endif
