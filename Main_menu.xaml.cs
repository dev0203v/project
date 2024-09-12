using Salmon.Models;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Salmon
{
    /// <summary>
    /// Main_menu.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Main_menu : Page
    {
        static public ObservableCollection<Basket> basketList = new ObservableCollection<Basket>();
        Basket basket1 = new Basket();
        Basket basket2 = new Basket();
        Basket basket3 = new Basket();
        Basket basket4 = new Basket();
        Basket basket5 = new Basket();
        Basket basket6 = new Basket();

        static public int total_price = 0;

        public Main_menu()
        {
            InitializeComponent();

        }

        private void btn_call_menu_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Call_menu.xaml", UriKind.Relative)
                );
        }

        private void btn_side_menu_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Side_menu.xaml", UriKind.Relative)
                );
        }

        private void btn_drink_menu_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Drink_menu.xaml", UriKind.Relative)
                );
        }
        private void btn_order_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
               new Uri("/Order.xaml", UriKind.Relative)
               );
            basketList.Clear();

            basket1.Menu_cnt = 0;
            basket2.Menu_cnt = 0;
            basket3.Menu_cnt = 0;
            basket4.Menu_cnt = 0;
            basket5.Menu_cnt = 0;
            basket6.Menu_cnt = 0;

        }

        private void btn_food1_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket1);

            basket1.Menu_name = "생연어초밥";
            basket1.Menu_cnt += 1;
            basket1.Menu_price = 25000;
            total_price += 25000;


            basketList.Add(basket1);

            listview_basket.ItemsSource = basketList;


            txt_total_price.Text = total_price.ToString() + "원";
        }

        private void btn_food2_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket2);

            basket2.Menu_name = "연어스테이크 샐러드";
            basket2.Menu_cnt += 1;
            basket2.Menu_price = 20000;
            total_price += 20000;

            basketList.Add(basket2);


            listview_basket.ItemsSource = basketList;

            txt_total_price.Text = total_price.ToString() + "원";
        }


        private void btn_food3_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket3);

            basket3.Menu_name = "연어사시미";
            basket3.Menu_cnt += 1;
            basket3.Menu_price = 30000;
            total_price += 30000;

            basketList.Add(basket3);

            listview_basket.ItemsSource = basketList;

            txt_total_price.Text = total_price.ToString() + "원";
        }

        private void btn_food4_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket4);

            basket4.Menu_name = "사케동";
            basket4.Menu_cnt += 1;
            basket4.Menu_price = 18000;
            total_price += 18000;

            basketList.Add(basket4);

            listview_basket.ItemsSource = basketList;

            txt_total_price.Text = total_price.ToString() + "원";
        }

        private void btn_food5_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket5);

            basket5.Menu_name = "생연어롤";
            basket5.Menu_cnt += 1;
            basket5.Menu_price = 15000;
            total_price += 15000;

            basketList.Add(basket5);

            listview_basket.ItemsSource = basketList;

            txt_total_price.Text = total_price.ToString() + "원";
        }

        private void btn_food6_Click(object sender, RoutedEventArgs e)
        {
            basketList.Remove(basket6);

            basket6.Menu_name = "연어스테이크";
            basket6.Menu_cnt += 1;
            basket6.Menu_price = 23000;
            total_price += 23000;

            basketList.Add(basket6);

            listview_basket.ItemsSource = basketList;

            txt_total_price.Text = total_price.ToString() + "원";
        }

        private void btn_logo_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
             new Uri("/home.xaml", UriKind.Relative)
             );

            basketList.Clear();

            basket1.Menu_cnt = 0;
            basket2.Menu_cnt = 0;
            basket3.Menu_cnt = 0;
            basket4.Menu_cnt = 0;
            basket5.Menu_cnt = 0;
            basket6.Menu_cnt = 0;
        }

    }
}
