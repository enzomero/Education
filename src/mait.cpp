#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void
avg ()
{
  uint32_t n;
  cin >> n;
  vector<int> temperatures (n);
  int64_t sum = 0;
  for (int& temperature : temperatures)
    {
      cin >> temperature;
      sum += temperature;
    }

  int64_t average = sum / static_cast<int64_t> (n);
  vector<uint32_t> result_indices;
  for (uint32_t i = 0; i < n; ++i)
    {
      if (temperatures[i] > average)
	{
	  result_indices.push_back (i);
	}
    }

  cout << result_indices.size () << endl;
  for (uint32_t result_index : result_indices)
    {
      cout << result_index << " ";
    }
  cout << endl;

}

uint64_t
bloks ()
{
  uint32_t numb = 0;
  int16_t densty = 0;
  int16_t side = 0;
  uint64_t volume = 0;
  uint64_t sum = 0; // without setting this var as 0, you will get (sum - 1) as result)
  cin >> numb;
  cin >> densty;
  if (numb == 0)
      return (sum);

  for (uint32_t i = 0; i < numb; i++)
    {
      for (uint16_t t = 0; t < 3; t++)
	{
	  cin >> side;
	  if (volume == 0)
	    {
	      volume = side;
	    }
	  else
	    {
	      volume *= side;
	    }
	}
      sum += volume * densty;
      volume = 0;
    }

  return (sum);
}


