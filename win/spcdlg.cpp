                                                                                                                        /*
--------------------------------------------------------------------------------
   win\spcdlg.cpp
   copyright(C) kyuhyun park
   1991
--------------------------------------------------------------------------------                                        */

#include <pub/config.hpp>
#include <pub/common.hpp>
#pragma hdrstop

#include <pub/dir.hpp>
#include <pub/point.hpp>
#include <pub/init.hpp>
#include <pub/misc.hpp>
#include <cnt/array.hpp>
#include <vio/textbrd.hpp>
#include <key/mac.hpp>
#include <win/spcdlg.hpp>

#define def_sel_brd_width   ( 16 )
#define def_sel_brd_height  ( 12 )
#define def_sel_brd_size    ( def_sel_brd_width * def_sel_brd_height )

#define def_win_width       ( 1+ 1+8+1 +def_sel_brd_width*2 + 1 +1 )
#define def_win_height      ( 1+ 1+def_sel_brd_height +1 + 1 )

#define def_page_x          ( 1+8+1 +1 )
#define def_page_y          ( 1 )

#define def_inp_line_x      ( 1+8+1 +1 )
#define def_inp_line_y      ( 1 + def_sel_brd_height + 1 )
#define def_inp_line_width  ( 16 )

#define def_menu_x          ( 2 )
#define def_menu_y          ( 1 )
#define def_menu_width      ( 8 )

#define def_null_char 0

struct cls_extent
{
   char* name_pch;
   int char_list_cnt;
   int char_list_inx;
};

static cls_extent extent_ary[]=
{
   { "琿ァ嫛选"  , 1, 0 },
   { "嫛选"      , 2, 1 },
   { "攅夺"      , 1, 3 },
   { "ゅ选"      ,10, 4 },
   { "夅"      , 1,14 },
   { "衑媔"      , 5,15 },
   { "磇蘟"    , 4,20 },
   { "珐ゥ"      , 2,24 },
   { "潯燼"      , 2,26 },
   { "媋煛痑"    , 2,28 },
   { "渁衰"      , 2,30 },
   { "溼碼"    , 2,32 }
};

static char* char_list_ach_ary[]=
{
   "詠詡詢詣詤詥試詧詨詩詪詫詬詭詮詯詰話該詳詴詵詶詷詸詺詻詼詽詾詿誀浴寓裕预豫驭鸳渊冤元垣袁原援辕园员圆猿源缘远苑愿怨院曰约越跃钥岳粤月悦阅耘云郧匀陨允运蕴酝晕韵孕匝砸杂栽哉灾宰载再在咱攒暂赞赃脏葬遭糟凿藻枣早澡蚤躁噪造皂灶燥责择则泽贼怎增憎曾赠扎喳渣札轧",
   "󱅖󱬰󲔊󲻤�9�:�;�<�=�>�?貮貯貰貱貲貳貴貵貶買貸貹貺費貼貽貾貿賀賁賂賃賄賅賆資賈賉賊\賋賌賍賎賏賐賑賒賓賔賕賖賗賘賙賚賛賜賝賞賟賠賡賢賣賤賥賦賧賨賩質賫賬賾賿贀贁贂贃贄贅贆贇贈贉贊贋贌贍",
   "佟佗伲伽佶佴侑侉侃侏佾佻侪佼侬侔俦俨俪俅俚俣俜俑俟俸倩偌俳倬倏倮倭俾倜倌倥倨偾偃偕偈偎偬偻傥傧傩傺僖儆僭僬僦僮儇儋仝氽佘佥俎龠汆籴兮巽黉馘",
   "󺔜󺻶󻣐󼊪�9�:�;�<�=�>�?蹳蹵蹷蹸蹹蹺蹻蹽蹾躀躂躃躄躆躈躉躊躋躌躍躎躑躒躓躕躖躗躘躙\躚躛躝躟躠躡躢躣躤躥躦躧躨躩躪躭躮躰躱躳躴躵躶躷躸躹躻躼躽躾躿軀軁軂軕",
   "鼙懿艹艽艿芏芊芨芄芎芑芗芙芫",
   "芸芾芰苈苊苣芘芷芮苋苌苁芩芴",
   "芡芪芟苄苎芤苡茉苷苤茏茇苜苴苒苘茌苻苓茑茚茆茔茕苠苕",
   "茜荑荛荜茈莒茼茴茱莛荞茯荏荇荃",
   "軦軧軨軩軪軫軬軭軮軯軰軱軲軳",
   "軴軵軶軷軸軹軺軻軼軽軾軿輀輁\",
   "輂較輄輅輆輇輈載輊輋輌輍輎輏輐輑輒輓輔輕輖輗輘輙輚輛",
   "輜輝輞輟輠輡輢輣輵輶輷輸輹輺輻",
   "荟荀茗荠茭茺茳荦荥",
   "輼輽輾輿轀轁轂轃轄",
   "邸邰郏郅邾郐郄郇郓郦郢郜郗郛郫郯郾鄄鄢鄞鄣鄱鄯鄹酃酆刍奂劢劬劭劾哿勐勖勰叟燮矍廴凵凼鬯厶弁畚巯坌垩垡塾墼壅壑圩圬圪圳圹圮圯坜圻坂坩垅坫垆",
   "凇冖冢冥讠讦讧讪讴讵讷诂诃诋诏诎诒诓诔诖诘诙诜诟诠诤诨诩诮诰",
   "诳诶诹诼诿谀谂谄谇谌谏谑谒谔谕谖谙谛谘谝谟",
   "谠",
   "谡谥谧谪谫谮谯谲谳谵谶卩卺阝阢阡阱阪阽阼陂陉陔陟陧陬陲陴隈隍隗隰邗邛",
   "邝邙邬邡邴邳邶邺",
   "󴊘󴱲󵙌󶀦�9�:�;�<�=�>�?贘贙贚贛贜贠赑趉趌趍趎趏趐跐跒跓跔",
   "贎贏贐贑贒贓贔贕贖贗",
   "赒赗赟赥赨赩赪赬赮赯赱赲\赸赹赺赻赼赽赾赿趀趂趃趆趇趈",
   "趒趓趕趖趗趘趙趚趛趜趝趞趠趡趹趻趽跀跁跂跅跇跈跉跊跍",
   "荨茛荩荬荪荭荮莰荸莳莴莠莪莓莜莅荼莶莩荽莸荻莘莞莨莺莼菁萁菥菘堇萘萋菝菽菖萜萸萑萆菔菟萏萃菸菹菪菅菀萦菰菡葜葑葚葙葳蒇蒈葺蒉葸萼葆葩葶蒌蒎萱葭蓁蓍蓐蓦蒽蓓蓊蒿蒺蓠蒡蒹",
   "􀞠􁅺􁭔􂔮�9�:�;�<�=�>�?轅轆轇轈轉轊轋轌轍轎轏轐轑轒轓轔轕轖轗轘轙轚轛轜轝轞轟轠轡\轢轣轤轥轪辀辌辒辝辠辡辢辤辥辦辧辪辬辭辮辯農辳辴辵辷辸辺辻込辿迀迃迆迲迴迵迶迺迻迼迾",
   "󷏚󷶴󸞎󹅨�9�:",
   "跕跘跙跜跠跡跢跥跦跧",
   "跶跼跾跿踀踁踂踃踄踆踇踈\踋踍踎踐踑踒踓踕踖踗踘踙",
   "踧踨踫踭踰踲踳踴踶踷踸踻踼踾蹜蹝蹞蹟蹠蹡蹢蹣蹤蹥",
   "堋堍埽埭堀堞堙塄堠塥塬墁墉墚墀馨",
   "󽙞󾀸󾨒󿏬�9�:�;�<�=�>�?軥",
   "蕖蔻蓿蓼蕙蕈蕨蕤蕞蕺瞢蕃蕲蕻薤薨薇薏蕹薮薜薅薹薷薰藓藁藜藿蘧蘅蘩蘖",
   "扪抟抻拊拚拗拮挢拶挹捋捃掭揶捱捺掎掴捭掬掊捩掮掼揲揸揠揿揄揞揎摒揆"
};

static tem_static_array<char16,def_sel_brd_size> cur_char_list;
static cls_boxed_point iter (def_sel_brd_width, def_sel_brd_size);
static cls_boxed_point extent (1, mac_cnt_of(extent_ary));
static bool exit_flg;

static tem_static_array<char16,def_spc_page_cmax> contents;
static int cnt;

static HWND frame;
static HWND client;

static cls_mac_runner* mac_runner;
static cls_mac_bin* mac_bin;
static cls_text_brd* brd;

static cls_spc_dlg* dlg;

inline char16 get_cur_char()
{
   return *cur_char_list.get_pnt(iter.get_index());
}

static void inverse_extent()
{
   brd->inverse_rect (def_menu_x , def_menu_y + extent.get_index(), def_menu_width, 1);
}

static void set_cur_char_list(int arg_inx)
{
   inverse_extent();
   extent.set_index(arg_inx);

   int inx = 0;
   int i;
   char* src;

   forcnt (i, extent_ary[extent.get_index()].char_list_cnt)
   {
      src = char_list_ach_ary [ extent_ary [ extent.get_index() ] . char_list_inx + i ];
      while ( *src )
      {
         cls_wchar wch = read_c16(&src);
         mac_assert (inx < def_sel_brd_size);
         *cur_char_list.get_pnt(inx++) = wch.c16;
      }
      while (inx % def_sel_brd_width)
      {
         mac_assert (inx < def_sel_brd_size);
         *cur_char_list.get_pnt(inx++) = def_null_char;
      }
   }

   while (inx < def_sel_brd_size)
   {
      *cur_char_list.get_pnt(inx++) = def_null_char;
   }

   int x;
   int y;
   forcnt (y, def_sel_brd_height)
   {
      brd->set_xy (def_page_x , def_page_y + y );
      forcnt (x, def_sel_brd_width)
      {
         char16 ch = *cur_char_list.get_pnt(y * def_sel_brd_width + x);
         if (ch) brd->write (ch);
         else brd->write_space(2);
      }
   }

   inverse_extent();
}

static void set_cur_char_list_rel(int inx_rel)
{
   set_cur_char_list (extent.get_index() + inx_rel);
}

static void first_char_list()
{
   set_cur_char_list (0);
}

static void last_char_list()
{
   set_cur_char_list (mac_cnt_of(extent_ary) - 1);
}

static void update_stock_line()
{
   brd->set_xy(def_inp_line_x , def_inp_line_y);

   int index = get_max (0, cnt - (def_inp_line_width-1));
   int i=0;

   while (i < def_inp_line_width-1 && index < cnt)
   {
      brd->write(*contents.get_pnt(index));
      index++;
      i++;
   }
   brd->write('<');
   brd->write_space((def_inp_line_width - i) * 2 - 1);
}

static bool append_to()
{
   bool rc = def_error;

   if (get_cur_char() != def_null_char)
   {
      *contents.get_pnt(cnt++) = get_cur_char();
      rc = def_ok;
   }

   return rc;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

void pdf_ok()
{
   if (!cnt) append_to();
   exit_flg = def_yes;
}

void pdf_cancel()
{
   exit_flg = def_yes;
}

void pdf_left()
{
   iter.set_x_rel(-1);
}

void pdf_right()
{
   iter.set_x_rel(1);
}

void pdf_up()
{
   iter.set_y_rel(-1);
}

void pdf_down()
{
   iter.set_y_rel(1);
}

void pdf_home()
{
   if (iter.is_x_first()) iter.set_first();
   else iter.set_x_first();
}

void pdf_end()
{
   if (iter.is_x_last()) iter.set_last();
   else iter.set_x_last();
}

void pdf_page_up()
{
   set_cur_char_list_rel(-1);
}

void pdf_page_down()
{
   set_cur_char_list_rel(1);
}

void pdf_left_acc()
{
   iter.set_x_rel(-4);
}

void pdf_right_acc()
{
   iter.set_x_rel(4);
}

void pdf_up_acc()
{
   iter.set_y_first();
}

void pdf_down_acc()
{
   iter.set_y_last();
}

void pdf_home_acc()
{
   iter.set_y_first();
}

void pdf_end_acc()
{
   iter.set_y_last();
}

void pdf_page_up_acc()
{
   first_char_list();
}

void pdf_page_down_acc()
{
   last_char_list();
}

int32 pdf_stock_add()
{
   return cnt < def_spc_page_cmax ? append_to() : def_error;
}

int32 pdf_stock_discard()
{
   return cnt ? (cnt--, def_ok) : def_error;
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void client_update()
{
   update_stock_line();
   brd->set_xy(def_page_x + iter.get_x()*2 , def_page_y + iter.get_y());
}

static void client_draw(HPS hps)
{
   brd->draw(hps);
}

static void client_draw()
{
   HPS hps = WinGetPS(client);
   client_draw(hps);
   WinReleasePS(hps);
}

static void client_key(cls_key_event* key_event)
{
   mac_assert(mac_runner);

   if (key_event->is_valid())
   {
      //int cnt = key_event->cnt;
      //while (cnt--)
      //{
         if (mac_runner->scan(key_event) == def_kb_scan_match)
         {
            mac_runner->execute();
            client_update();
            client_draw();
         }
      //}
   }
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static MRESULT client_wm_char(MPARAM mp1, MPARAM mp2)
{
   cls_key_event key_event((MPARAM)mp1, (MPARAM)mp2);
   client_key(&key_event);
   return (MRESULT) TRUE; // processed
}

static MRESULT client_wm_create(HWND /*hwnd*/)
{
   int i;

   brd = new cls_text_brd(def_win_width, def_win_height);

   brd->set_fg(def_clr_black);
   brd->set_bg(def_clr_white);
   brd->erase();
   brd->set_wide_cursor(def_yes);
   brd->show_cursor(def_yes);

   forcnt (i, mac_cnt_of(extent_ary))
   {
      brd->set_xy(def_menu_x, def_menu_y+i);
      brd->write(extent_ary[i].name_pch);
   }

   brd->set_fg(def_clr_white);
   brd->set_bg(def_clr_black);

   inverse_extent();

   cnt = 0;
   set_cur_char_list_rel(0);

   client_update();

   return 0; // continue creation
}

static MRESULT client_wm_destroy()
{
   delete brd;

   dlg->cnt = cnt;
   memcpy (dlg->contents, contents.get_base_pnt(), cnt * sizeof(char16));

   return 0; // reserved
}

static MRESULT client_wm_paint(HPS hps)
{
   brd->invalidate();
   client_draw(hps);
   return 0; // reserved
}

static MRESULT EXPENTRY client_proc(HWND hwnd, ULONG mline, MPARAM mp1, MPARAM mp2)
{
   MRESULT rc;

   switch (mline)
   {
      case WM_CHAR :    return client_wm_char(mp1, mp2);
      case WM_CREATE :  return client_wm_create(hwnd);
      case WM_DESTROY : return client_wm_destroy();
      case WM_PAINT :
         {
            HPS hps = WinBeginPaint (hwnd, 0, 0);
            rc = client_wm_paint(hps);
            WinEndPaint(hps);
         }
         return rc;
   }

   return WinDefWindowProc(hwnd, mline, mp1, mp2);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

static void frame_create()
{
   static bool registered_flg;
   static char client_cname[] = "spc_dlg_class";

   if (!registered_flg)
   {
      registered_flg = def_yes;
      WinRegisterClass (
         hab,
         client_cname,
         client_proc,
         CS_HITTEST,
         0
      );
   }

   ULONG flFrameFlags =
      //FCF_ICON |
      //FCF_MENU |
      FCF_SYSMODAL |
      FCF_NOBYTEALIGN |
      FCF_TITLEBAR |
      //FCF_SYSMENU |
      FCF_DLGBORDER
      //FCF_MINMAX |
      //FCF_HIDEBUTTON |
      //FCF_TASKLIST
      ;

   frame = WinCreateStdWindow (
      dlg->parent,
      /*WS_VISIBLE*/ 0,
      &flFrameFlags,
      client_cname,
      "Special Character Selector",
      WS_VISIBLE,
      0,
      0,
      &client
   );

   LONG cx_screen = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
   //LONG cy_screen = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

   RECTL rectl;

   rectl.xLeft   = 0;
   rectl.xRight  = def_win_width*8;
   rectl.yBottom = 0;
   rectl.yTop    = def_win_height*16;

   WinCalcFrameRect(frame, &rectl, FALSE);

   int frame_width  = rectl.xRight - rectl.xLeft;
   int frame_height = rectl.yTop - rectl.yBottom;

   int x = get_min(dlg->x + frame_width, cx_screen) - frame_width;
   int y = get_max(0, dlg->y - 1 - frame_height);

   WinSetWindowPos(
      frame,
      0,
      x, y,
      frame_width, frame_height,
      SWP_MOVE | SWP_SIZE
   );

   set_frame_activate(frame);
}

static void frame_destroy()
{
   WinDestroyWindow(frame);
}
                                                                                                                        /*
--------------------------------------------------------------------------------                                        */

cls_spc_dlg::cls_spc_dlg(HWND arg_parent, int arg_x, int arg_y, HWND arg_owner) :
   parent(arg_parent),
   x(arg_x),
   y(arg_y),
   owner(arg_owner),
   cnt(0)
{
}

void cls_spc_dlg::execute ()
{
   BOOL rc;

   dlg = this;
   exit_flg = def_no;

   rc = owner ? WinIsWindowEnabled(owner) : FALSE;
   if (rc) WinEnableWindow(owner, FALSE);

   frame_create();
   while (!exit_flg && WinGetMsg (hab, &qmsg, 0, 0, 0)) WinDispatchMsg (hab, &qmsg);
   frame_destroy();

   if (rc) WinEnableWindow(owner, TRUE);
}

#include <macro/tmp/spcdlg.def>
#include <macro/tmp/spcdlg.map>

static void ctor()
{
   try
   {
      mac_bin = new cls_mac_bin(cls_fname("@bindir/../macro/spcdlg.bin").get_path());
      mac_runner = new cls_mac_runner(mac_bin, mac_mapper);
   }
   catch (cls_xmsg xmsg)
   {
      xmsg.add_info("func: win/spcdlg.cpp/ctor()\ninfo: macro loading error\n");
      throw;
   }
}

static cls_initer initer(ctor);
