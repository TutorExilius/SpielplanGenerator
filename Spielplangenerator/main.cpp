#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

template <typename T>
std::vector<std::pair<T,T>> generatePlayingSchedule( std::vector<T> &members )
{
	if( members.size() % 2 != 0 )
	{
		members.push_back( members.at(0) );
		members.at(0) = T{};
	}

	std::vector<std::pair<T,T>> generatePlayingSchedule;
	const size_t N = members.size();

	if( N >= 2 )
	{
		for( int i = 0; i < N - 1; i++ )
		{
			T &corner = members.at(N-1);

			generatePlayingSchedule.push_back( 
				std::make_pair( corner, members.at( 0 ) ) );

			size_t left = 1;
			size_t right = N - 2;

			while( left < right )
			{
				generatePlayingSchedule.push_back( 
					std::make_pair( members.at(left), members.at( right ) ) );

				++left;
				--right;
			}	

			// Rotate here
			T tmp = members.at( 0 );

			for( int i = 0; i < N - 1; i++ )
			{
				members.at( i ) = members.at( i + 1 );
			}

			members.at( N - 2 ) = tmp;
		}
	}

	return generatePlayingSchedule;
}

int main()
{
	std::ifstream inFile{ R"(C:\Users\exi\Desktop\spieler.txt)" };

	if( !inFile )
	{
		std::cerr << "Could not open inFile" << std::endl;
		return -1;
	}

	std::vector<std::string> members;

	std::string line;
	while( getline( inFile, line ) )
	{
		if( line.size() > 0 )
		{
			members.push_back( line );
		}
	}
	
	auto ret = generatePlayingSchedule<std::string>( members );

	for( const auto& p : ret )
	{
		if( p.first == "" || p.second == "" )
			continue;

		std::cout << p.first << "\t" << p.second << std::endl;
	}

	return 0;
}