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
    /// Call_menu.xaml에 대한 상호 작용 논리
    /// </summary>
    public partial class Call_menu : Page
    {
  
        Basket basket1 = new Basket();
        Basket basket2 = new Basket();
        Basket basket3 = new Basket();
        Basket basket4 = new Basket();
        Basket basket5 = new Basket();

        public Call_menu()
        {
            InitializeComponent();
        }

        private void btn_main_menu_c_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Main_menu.xaml", UriKind.Relative));
        }

        private void btn_side_menu_c_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
                new Uri("/Side_menu.xaml", UriKind.Relative)
                );
        }

        private void btn_drink_menu_c_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(
            new Uri("/Drink_menu.xaml", UriKind.Relative)
             );
        }

        private void btn_order_c_Click(object sender, RoutedEventArgs e)
        {

            NavigationService.Navigate(
                new Uri("/Order.xaml", UriKind.Relative)
                );
            Main_menu.basketList.Clear();

            basket1.Menu_cnt = 0;
            basket2.Menu_cnt = 0;
            basket3.Menu_cnt = 0;
            basket4.Menu_cnt = 0;
            basket5.Menu_cnt = 0;

        }

        private void btn_call1_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket1);

            listview_basket.ItemsSource = Main_menu.basketList;

            basket1.Menu_name = "와사비";
            basket1.Menu_cnt += 1;
            basket1.Menu_price = 0;

            Main_menu.basketList.Add(basket1);
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";

            listview_basket.ItemsSource = Main_menu.basketList;

        }

        private void btn_call2_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket2);

            listview_basket.ItemsSource = Main_menu.basketList;

            basket2.Menu_name = "간장";
            basket2.Menu_cnt += 1;
            basket2.Menu_price = 0;

            Main_menu.basketList.Add(basket2);
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";

            listview_basket.ItemsSource = Main_menu.basketList;
        }

        private void btn_call3_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket3);

            listview_basket.ItemsSource = Main_menu.basketList;

            basket3.Menu_name = "초생강";
            basket3.Menu_cnt += 1;
            basket3.Menu_price = 0;

            Main_menu.basketList.Add(basket3);
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";

            listview_basket.ItemsSource = Main_menu.basketList;
        }

        private void btn_call4_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket4);

            listview_basket.ItemsSource = Main_menu.basketList;

            basket4.Menu_name = "물";
            basket4.Menu_cnt += 1;
            basket4.Menu_price = 0;

            Main_menu.basketList.Add(basket4);
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";

            listview_basket.ItemsSource = Main_menu.basketList;
        }

        private void btn_call5_Click(object sender, RoutedEventArgs e)
        {
            Main_menu.basketList.Remove(basket5);

            listview_basket.ItemsSource = Main_menu.basketList;

            basket5.Menu_name = "단무지";
            basket5.Menu_cnt += 1;
            basket5.Menu_price = 0;

            Main_menu.basketList.Add(basket5);
            txt_total_price.Text = Main_menu.total_price.ToString() + "원";

            listview_basket.ItemsSource = Main_menu.basketList;
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
            basket4.Menu_cnt = 0;
            basket5.Menu_cnt = 0;
        }
    }
}
