#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class Lang
{
  DE, FR, IT
};

struct Region
{
  string std_name;
  string pattern_std_name;
  map<Lang, string> names;
  int64_t population;
};

int
FindMaxRepetitionCount (const vector<Region>& regions)
{
  if (regions.size() == 0 )
    return (0);

  int result = 1;
  for (auto item : regions)
    {
      int counter = 0;
      for (auto subitem : regions)
	{
	  (item.std_name == subitem.std_name &&
	   item.pattern_std_name == subitem.pattern_std_name &&
	   item.names == subitem.names &&
	   item.population == subitem.population
	      ) ? ++counter : counter;
	}
      result > counter ? result : result = counter;
    }
  return (result);
}

/*
int
main ()
{
    cout << FindMaxRepetitionCount (
    {
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 89 },

      { "Russia", "Eurasia",
	{
	  { Lang::DE, "Russland" },
	  { Lang::FR, "Russie" },
	  { Lang::IT, "Russia" } }, 89 },
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 89 },
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 89 },
      { "Russia", "Eurasia",
	{
	  { Lang::DE, "Russland" },
	  { Lang::FR, "Russie" },
	  { Lang::IT, "Russia" } }, 89 }, }) << endl;

  cout << FindMaxRepetitionCount (
    {
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 89 },
      { "Russia", "Eurasia",
	{
	  { Lang::DE, "Russland" },
	  { Lang::FR, "Russie" },
	  { Lang::IT, "Russia" } }, 89 },
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou deux" },
	  { Lang::IT, "Mosca" } }, 89 },
      { "Moscow", "Toulouse",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 89 },
      { "Moscow", "Russia",
	{
	  { Lang::DE, "Moskau" },
	  { Lang::FR, "Moscou" },
	  { Lang::IT, "Mosca" } }, 31 }, }) << endl;

  return 0;
}
*/
