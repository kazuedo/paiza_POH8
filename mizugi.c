#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define D_DEBUG
//#define D_TEST

#ifdef D_DEBUG
#define D_OK	(0)
#define D_NG	(1)
#define D_LOG(...) fprintf( stderr, "%s(%d):", __func__, __LINE__ ); printf( __VA_ARGS__ ); printf( "\n" );
#else
#define D_LOG(...)
#endif

#define D_OUT_MAX_LENGTH	(100000 * 3)
#define D_CHAR_KIND_NUM	(26)

typedef struct {
	int n;
	int m;
	char s[100000];
	char t[100000];
} in_t;

static void count( const char* str, int len, int *list )
{
	int i;
	const char *p = str;
	D_LOG( "len:%d, str:%s", len, str );
	for( i = 0; i < len; i++ ) {
		list[ *p - 'a' ]++;
		p++;
	}
}

static void exec( in_t* in, char* out )
{
	int result = 0, i;
	int ls[D_CHAR_KIND_NUM];
	int lt[D_CHAR_KIND_NUM];
	memset( ls, 0, sizeof( ls ) );
	memset( lt, 0, sizeof( lt ) );

	count( in->s, in->n, ls );
	count( in->t, in->m, lt );
	for( i = 0; i < D_CHAR_KIND_NUM; i++ ){
		if( ls[i] < lt[i] ) {
			result += lt[i] - ls[i];
		}
	}
	sprintf( out, "%d\n", result );
}

static void print_in( in_t *in )
{
	D_LOG( "[in] n:%d, m:%d", in->n, in->m );
	D_LOG( "[in] s:%s", in->s );
	D_LOG( "[in] t:%s", in->t );
}

#ifndef D_TEST
static void get_param( in_t* in )
{
	scanf( "%d %d", &in->n, &in->m );
	fflush( stdin );
	scanf( "%s", in->s );
	fflush( stdin );
	scanf( "%s", in->t );
	fflush( stdin );

	print_in( in );
}
#else
static void get_param_test( in_t* in, char* in_str )
{
	char *p;
	char *buf = (char*)malloc( strlen( in_str ) + 1 );
	memcpy( buf, in_str, strlen( in_str ) );

	p = strtok( buf, "\n" );
	sscanf( p, "%d %d", &in->n, &in->m );
	
	p = strtok( NULL, "\n" );
	sscanf( p, "%s", in->s );

	p = strtok( NULL, "\n" );
	sscanf( p, "%s", in->t );

	print_in( in );

	free( buf );
}

static int test( char* in_str, const char* expect )
{
	static int testn = 0;
	in_t in;
	char out[D_OUT_MAX_LENGTH];

	testn++;
	memset( out, 0, sizeof( out ) );
	get_param_test( &in, in_str );
	exec( &in, out );

	if( strncmp( out, expect, strlen( out ) ) == 0 ){
		D_LOG( "[%d:OK]", testn );
		return D_OK;
	} else {
		D_LOG( "[%d:NG]", testn );
		D_LOG( "--- in ---\n%s--- out ---\n%s--- expect---\n%s", in_str, out, expect );
		return D_NG;
	}
}
#endif

int main( int argc, char* argv[])
{
#ifdef D_TEST
	test( "5 5\npizza\npaiza\n", "1\n" );
	test( "3 5\nant\nmaven\n", "3\n" );
	test( "1 27\na\nabcdefghijklmnopqrstuvwxyza\n", "26\n" );
	test( "27 1\nabcdefghijklmnopqrstuvwxyza\na\n", "0\n" );
#else
	in_t in;
	char out[D_OUT_MAX_LENGTH];
	get_param( &in );
	exec( &in, out );
	printf( "%s", out );
#endif
	
	return 0;
}
