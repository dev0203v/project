using Salmon.Models;
using System;
using System.Buffers.Text;
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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Salmon
{
    /// <summary>
    /// Side_menu.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Side_menu : Page
    {
        Basket basket = new Basket();
        Basket basket1 = new Basket();
        Basket basket2 = new Basket();
        Basket basket3 = new Basket();
        public Side_menu()
        {
            InitializeComponent();
        }

        private void btn_main_menu_c_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Main_menu.xaml", UriKind.Relative)
                );
        }

        private void btn_call_menu_s_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Call_menu.xaml", UriKind.Relative)
                );
        }

        private void btn_drink_menu_s_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
               new Uri("/Drink_menu.xaml", UriKind.Relative)
               );
        }
        private void btn_order_s_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Order.xaml", UriKind.Relative)
                );
            Main_menu.basketList.Clear();

            basket1.Menu_cnt = 0;
            basket2.Menu_cnt = 0;
            basket3.Menu_cnt = 0;
        }

        private void btn_side1_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket1);

            basket1.Menu_name = "왕새우튀김";
            basket1.Menu_cnt += 1;
            basket1.Menu_price = 10000;
            Main_menu.total_price += 10000;

            Main_menu.basketList.Add(basket1);

            listview_basket.ItemsSource = Main_menu.basketList;

            txt_total_price.Text = Main_menu.total_price.ToString() + "원";
        }

        private void btn_side2_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket2);

            basket2.Menu_name = "치킨가라아게";
            basket2.Menu_cnt += 1;
            basket2.Menu_price = 12000;
            Main_menu.total_price += 12000;

            Main_menu.basketList.Add(basket2);

            listview_basket.ItemsSource = Main_menu.basketList;

            txt_total_price.Text = Main_menu.total_price.ToString() + "원";
        }

        private void btn_side3_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket3);


            basket3.Menu_name = "공기밥";
            basket3.Menu_cnt += 1;
            basket3.Menu_price = 2000;
            Main_menu.total_price += 2000;

            Main_menu.basketList.Add(basket3);

            listview_basket.ItemsSource = Main_menu.basketList;

            txt_total_price.Text = Main_menu.total_price.ToString() + "원";
        }

        private void btn_logo_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/home.xaml", UriKind.Relative)
            );

            Main_menu.basketList.Clear();

            basket1.Menu_cnt = 0;
            basket2.Menu_cnt = 0;
            basket3.Menu_cnt = 0;


        }
    }
}
