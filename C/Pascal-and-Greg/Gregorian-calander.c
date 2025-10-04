#include <stdio.h> /* importing library to be able to use printf */
#include "convert_integer.h"
int weekday(int year, int month, int day);
int weeknumber(int ordinalday, int weekdaynumb, int year);
int isoyear(int day, int month, int year, int weeknumb);
int ordinalday(int day, int month, int year);
int newfloor(float numb);
int leap(int year);
int p (int year);
int weeks_in_year(int year);
int main(int argc, char **argv)
{
  int day;
  int month;
  int year;
  int ordday;
  int isoweeknumb;
  int week;
  int iso_year;

  
  day = get_integer();
 
  month = get_integer();
  
  year = get_integer();
  
  /*CALENDAR DATE*/
  printf("%d",year);
  printf("-%02d",month);
  printf("-%02d\n",day);
  
  /*ORDINAL DATE*/
  printf("%d",year);
  ordday=ordinalday(day,month,year);
  printf("-%03d\n",ordday);
  
  /*WEEK DATE*/
  week=weekday(year,month, day);
  week=week-1;
  if (week == -1)
  {
  week=6;
  }
  else if (week == 0)
  {
  week=7;
  }


  isoweeknumb=weeknumber(ordday, week, year);
  
  iso_year=isoyear(day,month,year,isoweeknumb);
  
  printf("%d",iso_year);
  printf("-W%02d",isoweeknumb);
  printf("-%d\n",week);
  

  
  return 0;
}


int weekday(year,month,day)
{ int first;
  int weekdaynumb;
  int add;

  if ((month == 1) || (month==2))
  {
    month= month + 12;
    year = year -1;
  }

  first= ((1 + 5 * ((year - 1) % 4) + 4 * ((year - 1) % 100) + 6 * ((year - 1) % 400) ) % 7);
  
  add=ordinalday(day,month,year);

  weekdaynumb=(first+add)%7;
  return weekdaynumb;
}




int p(year)
{
  int p;
  p= (year + year / 4 - year / 100 + year / 400)% 7;
  return p;
}


int weeks_in_year(year)
{
  int weeksinyear;
  if ((p(year) == 4) || (p(year - 1) == 3))
    {
		weeksinyear = 53;
    }
  else
  {
	weeksinyear = 52;
  }
  return weeksinyear;
}



int weeknumber(ordinalday,weekdaynumb, year)
{
  int isoweeknumb;
  isoweeknumb= newfloor(((ordinalday-weekdaynumb) +10)/7);
  if (isoweeknumb == 0)
  {
    isoweeknumb= weeks_in_year(year-1);
  }
  if (isoweeknumb > weeks_in_year(year))
  {
    if (weekdaynumb<4)
    {
      isoweeknumb= 1;
    }
  }
  return isoweeknumb;
}



/*The ISO year is straightforward to work out for the ISO week returned by this algorithm. If the calendar month is December and the ISO week returned is 1, then the ISO year is the year following the calendar year. If the calendar month is January and ISO week returned is 52 or 53 then the ISO year is the previous calendar year.*/

int isoyear(day,month,year,weeknumb)
{
  int isoyear;
  isoyear=year;
  if ((month==12) && (weeknumb==1))
  {
    isoyear=isoyear+1;
  }
  else if ((month==1) &&((weeknumb==52) ||(weeknumb==53)))
  {
    isoyear=isoyear-1;
  }
  return isoyear;
}




int ordinalday(day,month,year)
{
  int ordday;
  if (month==1)/*if month is january */
  {
    return day;
  }
  else if (month==2)/* if month is february (only need to add the days in january on)*/
  {
    return day+31;
  }
  else
  {
    ordday= newfloor(30.6*month-91.4)+day;

    if (leap(year)==1)
    {
      return ordday+60;
    }
  }
  return ordday+59;
}




int leap(year)
{
    if ((year % 4)== 0)
    {
      if ((year % 100)==0)
      {
        if ((year % 400)==0)
          {
          return 1;
          }
      }
      else
      {
        return 1;
      }
    }

    return 0;
}




int newfloor(float numb)
{
  int minuses;
  minuses=0;
  while ((numb-1)>=0)
  {
    numb=numb-1;
    /*printf("\npointer: %d!!!",minuses);*/
    minuses=minuses+1;
  }

  return minuses;
  
}
  


