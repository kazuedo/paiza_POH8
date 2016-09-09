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

#define D_OUT_MAX_LENGTH	(10000)

typedef struct {
	int n;
	int p;
	int m;
	int q;
} in_t;

static void exec( in_t* in, char* out )
{
	int result = 0;

	result += in->n * in->p;
	result += ( in->n / in->m ) * in->q;
	result += ( in->n % in->m ) ? in->q : 0;
	sprintf( out, "%d\n", result );
}

static void print_in( in_t *in )
{
	D_LOG( "n:%d, p:%d, m:%d, q:%d", in->n, in->p, in->m, in->q );
}

#ifndef D_TEST
static void get_param( in_t* in )
{
	scanf( "%d %d", &in->n, &in->p );
	fflush( stdin );
	scanf( "%d %d", &in->m, &in->q );
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
	sscanf( p, "%d %d", &in->n, &in->p );
	
	p = strtok( NULL, "\n" );
	sscanf( p, "%d %d", &in->m, &in->q );

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
	test( "100 110\n20 200\n", "12000\n" );
	test( "980 200\n200 1000\n", "201000\n" );
#else
	in_t in;
	char out[D_OUT_MAX_LENGTH];
	get_param( &in );
	exec( &in, out );
	printf( "%s", out );
#endif
	
	return 0;
}
