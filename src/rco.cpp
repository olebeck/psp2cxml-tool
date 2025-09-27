
#include "cxml/cxml.h"
#include "rcs.h"
#include "rco.h"
#include <inttypes.h>


rco::compiler::compiler(){
	SetMagic("RCOF");
	SetVersion(CXML_VERSION(1, 1, 0));

	append_schema({
		"alias",
		{"aliastable"},
		{
			{"org_id", cxml::attr_type_idhashref},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"aliastable",
		{"resource"},
		{
		}
	});
	append_schema({
		"app_icon_simple",
		{"button", "list_item", "template", "group", "text", "plane", "box"},
		{
			{"appearance", cxml::attr_type_int},
			{"enable_tap", cxml::attr_type_int},
			{"id",         cxml::attr_type_hash},
			{"texture",    cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"banner_button",
		{"list_item"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"box",
		{"rich_text", "template", "scroll_view", "button", "list_item", "box", "plane", "radio_box", "speech_balloon", "group", "dialog", "radio_button", "page", "composite_drawer", "plane_button", "image_button"},
		{
			{"style",          cxml::attr_type_idhashref},
			{"id",             cxml::attr_type_hash},
			{"exclusive_list", cxml::attr_type_string},
			{"hit_ignore",     cxml::attr_type_int},
			{"texture",        cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"browser_rich_text",
		{"group", "box"},
		{
			{"style",    cxml::attr_type_idhashref},
			{"id",       cxml::attr_type_hash},
			{"w_sbar_v", cxml::attr_type_hash}
		}
	});
	append_schema({
		"busyindicator",
		{"list_item", "text", "group", "page", "plane", "list_view", "template", "box", "scroll_view", "rich_text", "button"},
		{
			{"style",   cxml::attr_type_idhashref},
			{"id",      cxml::attr_type_hash},
			{"texture", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"button",
		{"plane", "rich_text", "box", "list_item", "group", "text_box", "button", "template", "text", "page", "image_button", "pagetable", "composite_drawer", "scroll_view", "plane_shadow", "speech_balloon"},
		{
			{"style",                              cxml::attr_type_idhashref},
			{"enable_long_press_text_auto_scroll", cxml::attr_type_int},
			{"id",                                 cxml::attr_type_hash},
			{"texture",                            cxml::attr_type_idhashref},
			{"label",                              cxml::attr_type_idhashref},
			{"sound",                              cxml::attr_type_idhashref},
			{"enable",                             cxml::attr_type_int}
		}
	});
	append_schema({
		"button_base",
		{"template"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"check_box",
		{"rich_text", "box", "button", "plane", "group", "text", "list_item", "template", "text_box", "image_button"},
		{
			{"id",    cxml::attr_type_hash},
			{"style", cxml::attr_type_idhashref},
			{"sound", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"color_change_button",
		{"plane", "group"},
		{
			{"style",                              cxml::attr_type_idhashref},
			{"enable_long_press_text_auto_scroll", cxml::attr_type_int},
			{"id",                                 cxml::attr_type_hash},
			{"texture",                            cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"color_shift_button",
		{"list_item", "group"},
		{
			{"press_color",                        cxml::attr_type_floatarray},
			{"style",                              cxml::attr_type_idhashref},
			{"enable_long_press_text_auto_scroll", cxml::attr_type_int},
			{"id",                                 cxml::attr_type_hash},
			{"default_color",                      cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"composite_button",
		{"group", "box", "template"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash},
			{"sound", cxml::attr_type_idhashref},
			{"str1",  cxml::attr_type_idhashref},
			{"tex0",  cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"composite_drawer",
		{"box", "scroll_view", "plane", "group", "template", "button_base"},
		{
			{"id",    cxml::attr_type_hash},
			{"style", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"corner_button",
		{"page", "template", "plane", "group", "pagetable"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"dialog",
		{"template"},
		{
			{"style",          cxml::attr_type_idhashref},
			{"id",             cxml::attr_type_hash},
			{"exclusive_list", cxml::attr_type_string}
		}
	});
	append_schema({
		"directbar",
		{"template"},
		{
			{"style",        cxml::attr_type_idhashref},
			{"launchbtn_y",  cxml::attr_type_float},
			{"balloon_type", cxml::attr_type_int},
			{"texture",      cxml::attr_type_idhashref},
			{"label",        cxml::attr_type_idhashref},
			{"hitmargin",    cxml::attr_type_float},
			{"id",           cxml::attr_type_hash}
		}
	});
	append_schema({
		"drop_shadow_button",
		{"group", "plane", "color_shift_button", "text", "template"},
		{
			{"shadow_color",                       cxml::attr_type_floatarray},
			{"shadow_press_blur_factor",           cxml::attr_type_float},
			{"shadow_scale",                       cxml::attr_type_floatarray},
			{"shadow_texture_no",                  cxml::attr_type_int},
			{"shadow_press_pos",                   cxml::attr_type_floatarray},
			{"shadow_pos",                         cxml::attr_type_floatarray},
			{"texture",                            cxml::attr_type_idhashref},
			{"shadow_ofs",                         cxml::attr_type_floatarray},
			{"shadow_press_color",                 cxml::attr_type_floatarray},
			{"style",                              cxml::attr_type_idhashref},
			{"enable_long_press_text_auto_scroll", cxml::attr_type_int},
			{"shadow_blur_factor",                 cxml::attr_type_float},
			{"id",                                 cxml::attr_type_hash}
		}
	});
	append_schema({
		"file",
		{"filetable"},
		{
			{"origsize", cxml::attr_type_int},
			{"src",      cxml::attr_type_filename},
			{"type",     cxml::attr_type_string},
			{"id",       cxml::attr_type_idhash},
			{"compress", cxml::attr_type_string}
		}
	});
	append_schema({
		"file_list",
		{"plane", "template", "box", "composite_drawer"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"filetable",
		{"resource"},
		{
		}
	});
	append_schema({
		"five_star_plane",
		{"template", "group", "box"},
		{
			{"off_texture", cxml::attr_type_idhashref},
			{"style",       cxml::attr_type_idhashref},
			{"id",          cxml::attr_type_hash},
			{"on_texture",  cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"focus_hint",
		{"color_change_button", "drop_shadow_button", "button", "color_shift_button", "image_button", "text_box", "radio_button", "corner_button", "plane_button", "check_box", "update_button", "list_view", "plane", "list_item", "num_spin", "group", "app_icon_simple", "file_list", "box", "composite_button", "button_base"},
		{
			{"focus_offset",  cxml::attr_type_floatarray},
			{"focus_size",    cxml::attr_type_floatarray},
			{"focus_shape",   cxml::attr_type_int},
			{"focus_rot",     cxml::attr_type_floatarray},
			{"focus_texture", cxml::attr_type_idhashref},
			{"right_id",      cxml::attr_type_hash},
			{"left_id",       cxml::attr_type_hash},
			{"down_id",       cxml::attr_type_hash},
			{"up_id",         cxml::attr_type_hash},
			{"direct_key",    cxml::attr_type_int},
			{"enable",        cxml::attr_type_int}
		}
	});
	append_schema({
		"group",
		{"page", "plane", "group", "template", "list_item", "box", "scroll_view", "rich_text", "plane_shadow", "plane_button"},
		{
			{"id", cxml::attr_type_hash}
		}
	});
	append_schema({
		"id",
		{"idtable"},
		{
			{"id", cxml::attr_type_hash}
		}
	});
	append_schema({
		"idtable",
		{"resource"},
		{
		}
	});
	append_schema({
		"image_button",
		{"plane", "box", "list_item", "group", "template"},
		{
			{"style",                              cxml::attr_type_idhashref},
			{"id",                                 cxml::attr_type_hash},
			{"sound",                              cxml::attr_type_idhashref},
			{"label",                              cxml::attr_type_idhashref},
			{"enable",                             cxml::attr_type_int},
			{"enable_long_press_text_auto_scroll", cxml::attr_type_int},
			{"texture",                            cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"image_slidebar",
		{"box"},
		{
			{"style",       cxml::attr_type_idhashref},
			{"base_mode",   cxml::attr_type_int},
			{"texture",     cxml::attr_type_idhashref},
			{"texture_bar", cxml::attr_type_idhashref},
			{"tex_mode",    cxml::attr_type_int},
			{"id",          cxml::attr_type_hash}
		}
	});
	append_schema({
		"layout_box",
		{"box"},
		{
			{"bottom_margin",     cxml::attr_type_float},
			{"boundary_mode_x",   cxml::attr_type_int},
			{"space",             cxml::attr_type_float},
			{"align",             cxml::attr_type_intarray},
			{"top_margin",        cxml::attr_type_float},
			{"id",                cxml::attr_type_hash},
			{"adjust",            cxml::attr_type_intarray},
			{"layout_type",       cxml::attr_type_int},
			{"anchor",            cxml::attr_type_intarray},
			{"children_align_y",  cxml::attr_type_int},
			{"pos",               cxml::attr_type_floatarray},
			{"children_align_x",  cxml::attr_type_int},
			{"space_adjust",      cxml::attr_type_int},
			{"children_adjust_y", cxml::attr_type_int},
			{"children_adjust_x", cxml::attr_type_int},
			{"size",              cxml::attr_type_floatarray},
			{"min_size",          cxml::attr_type_floatarray},
			{"right_margin",      cxml::attr_type_float},
			{"left_margin",       cxml::attr_type_float},
			{"max_size",          cxml::attr_type_floatarray},
			{"origin",            cxml::attr_type_intarray},
			{"boundary_mode_y",   cxml::attr_type_int},
			{"children_height",   cxml::attr_type_float},
			{"alpha",             cxml::attr_type_float}
		}
	});
	append_schema({
		"layout_dialog",
		{"dialog"},
		{
			{"children_adjust_y", cxml::attr_type_int},
			{"children_adjust_x", cxml::attr_type_int},
			{"layout_type",       cxml::attr_type_int},
			{"adjust",            cxml::attr_type_intarray},
			{"size",              cxml::attr_type_floatarray},
			{"pos",               cxml::attr_type_floatarray},
			{"id",                cxml::attr_type_hash},
			{"min_size",          cxml::attr_type_floatarray},
			{"align",             cxml::attr_type_intarray}
		}
	});
	append_schema({
		"layout_hint",
		{"group", "plane", "color_change_button", "list_view", "text", "drop_shadow_button", "button", "rich_text", "check_box", "scrollbar_touch", "plane_button", "list_item", "scroll_view", "box", "busyindicator", "color_shift_button", "progressbar", "image_button", "text_box", "radio_button", "corner_button", "speech_balloon", "radio_box", "five_star_plane", "browser_rich_text", "thumbnail_button", "scrollbar", "image_slidebar", "file_list", "sliding_drawer", "progressbar_touch", "update_button", "directbar", "template", "slidebar", "page", "composite_drawer", "plane_shadow", "num_spin", "list_edge", "webview", "app_icon_simple", "style_plane", "composite_button", "button_base"},
		{
			{"origin", cxml::attr_type_intarray},
			{"align",  cxml::attr_type_intarray},
			{"pos",    cxml::attr_type_floatarray},
			{"id",     cxml::attr_type_hash},
			{"adjust", cxml::attr_type_intarray},
			{"alpha",  cxml::attr_type_float},
			{"rot",    cxml::attr_type_floatarray},
			{"anchor", cxml::attr_type_intarray},
			{"size",   cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"list_edge",
		{"template"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"list_item",
		{"template", "list_item"},
		{
			{"id",                      cxml::attr_type_hash},
			{"style",                   cxml::attr_type_idhashref},
			{"text_auto_scroll_target", cxml::attr_type_hash}
		}
	});
	append_schema({
		"list_view",
		{"plane", "group", "box", "template", "page", "plane_shadow"},
		{
			{"style",             cxml::attr_type_idhashref},
			{"id",                cxml::attr_type_hash},
			{"sbar_fadeout_time", cxml::attr_type_float},
			{"w_sbar_v",          cxml::attr_type_hash},
			{"sound",             cxml::attr_type_idhashref},
			{"w_sbar_h",          cxml::attr_type_hash}
		}
	});
	append_schema({
		"locale",
		{"stringtable"},
		{
			{"origsize", cxml::attr_type_int},
			{"src",      cxml::attr_type_filename},
			{"compress", cxml::attr_type_string},
			{"id",       cxml::attr_type_id}
		}
	});
	append_schema({
		"num_spin",
		{"box"},
		{
			{"id",   cxml::attr_type_hash},
			{"loop", cxml::attr_type_int}
		}
	});
	append_schema({
		"override_alias",
		{"alias"},
		{
			{"model_type", cxml::attr_type_int},
			{"org_id",     cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"override_template_ref",
		{"template_ref"},
		{
			{"resolution", cxml::attr_type_hash},
			{"template",   cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"override_texture",
		{"texture"},
		{
			{"model_type",                cxml::attr_type_int},
			{"src",                       cxml::attr_type_filename},
			{"origsize",                  cxml::attr_type_int},
			{"compress",                  cxml::attr_type_string},
			{"type",                      cxml::attr_type_string},
			{"margin_v",                  cxml::attr_type_intarray},
			{"margin_h",                  cxml::attr_type_intarray},
			{"ignore_make_surface_first", cxml::attr_type_string}
		}
	});
	append_schema({
		"page",
		{"pagetable"},
		{
			{"id",       cxml::attr_type_idhash},
			{"origin",   cxml::attr_type_intarray},
			{"style",    cxml::attr_type_idhashref},
			{"template", cxml::attr_type_idhashref},
			{"layouter", cxml::attr_type_string}
		}
	});
	append_schema({
		"pagetable",
		{"resource"},
		{
		}
	});
	append_schema({
		"plane",
		{"group", "plane", "page", "rich_text", "list_item", "drop_shadow_button", "template", "box", "button", "color_shift_button", "text", "radio_box", "dialog", "sliding_drawer", "image_button", "progressbar_touch", "scroll_view", "plane_button", "text_box", "slidebar", "pagetable", "plane_shadow", "list_edge", "app_icon_simple", "check_box", "composite_button"},
		{
			{"style",      cxml::attr_type_idhashref},
			{"id",         cxml::attr_type_hash},
			{"texture",    cxml::attr_type_idhashref},
			{"hit_ignore", cxml::attr_type_int}
		}
	});
	append_schema({
		"plane_button",
		{"plane", "page", "group", "text_box", "template", "list_item", "app_icon_simple", "composite_button", "composite_drawer", "text"},
		{
			{"style",   cxml::attr_type_idhashref},
			{"id",      cxml::attr_type_hash},
			{"sound",   cxml::attr_type_idhashref},
			{"texture", cxml::attr_type_idhashref},
			{"enable",  cxml::attr_type_int}
		}
	});
	append_schema({
		"plane_shadow",
		{"page", "box"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"planeobj",
		{"style_plane", "style_drop_shadow_plane", "style_button", "style_drop_shadow_button", "style_list_item", "style_list_view", "style_color_change_button", "style_scrollbar", "style_rich_text", "style_scrollbar_touch", "style_image_button", "style_text", "style_box", "style_speech_balloon", "style_text_box", "style_radio_button", "style_image_slidebar", "style_scroll_view", "style_banner_button", "style_browser_rich_text", "style_five_star_plane", "style_thumbnail_button", "style_plane_button", "style_file_list", "style_progressbar", "style_progressbar_touch", "style_update_button", "style_corner_button", "style_directbar", "style_slidebar", "style_check_box", "style_plane_shadow", "style_scrollbar2d", "style_composite_button", "style_composite_drawer", "style_webview", "style_mapview"},
		{
			{"id",                  cxml::attr_type_hash},
			{"tex_region",          cxml::attr_type_floatarray},
			{"scale_mode_y",        cxml::attr_type_int},
			{"scale_mode_x",        cxml::attr_type_int},
			{"blend",               cxml::attr_type_int},
			{"scale_value",         cxml::attr_type_floatarray},
			{"texture0",            cxml::attr_type_idhashref},
			{"color",               cxml::attr_type_floatarray},
			{"size",                cxml::attr_type_floatarray},
			{"reduce_transparency", cxml::attr_type_int},
			{"align_y",             cxml::attr_type_int},
			{"pos",                 cxml::attr_type_floatarray},
			{"texture1",            cxml::attr_type_idhashref},
			{"align_x",             cxml::attr_type_int}
		}
	});
	append_schema({
		"progressbar",
		{"box", "plane", "button", "template", "group", "page", "plane_button"},
		{
			{"style",          cxml::attr_type_idhashref},
			{"label_pos_mode", cxml::attr_type_int},
			{"id",             cxml::attr_type_hash},
			{"w_label",        cxml::attr_type_hash},
			{"signal_anim",    cxml::attr_type_int},
			{"label_mode",     cxml::attr_type_int},
			{"label_margin",   cxml::attr_type_float},
			{"bar_mode",       cxml::attr_type_int}
		}
	});
	append_schema({
		"progressbar_touch",
		{"plane"},
		{
			{"style",          cxml::attr_type_idhashref},
			{"label_pos_mode", cxml::attr_type_int},
			{"w_label",        cxml::attr_type_hash},
			{"label_mode",     cxml::attr_type_int},
			{"label_margin",   cxml::attr_type_float},
			{"id",             cxml::attr_type_hash},
			{"bar_mode",       cxml::attr_type_int}
		}
	});
	append_schema({
		"radio_box",
		{"plane", "text", "box", "page", "template"},
		{
			{"id",    cxml::attr_type_hash},
			{"style", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"radio_button",
		{"box", "template", "radio_box"},
		{
			{"id",    cxml::attr_type_hash},
			{"style", cxml::attr_type_idhashref},
			{"tuck",  cxml::attr_type_int}
		}
	});
	append_schema({
		"resolution",
		{"layout_box", "layout_hint"},
		{
			{"size", cxml::attr_type_floatarray},
			{"id",   cxml::attr_type_hash},
			{"pos",  cxml::attr_type_floatarray},
			{"rot",  cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"resource",
		cxml::schema::item::NoneParent,
		{
			{"version", cxml::attr_type_float},
			{"type",    cxml::attr_type_string},
			{"id",      cxml::attr_type_idhash}
		}
	});
	append_schema({
		"rich_text",
		{"plane", "template", "page", "group", "box"},
		{
			{"style",    cxml::attr_type_idhashref},
			{"w_sbar_v", cxml::attr_type_hash},
			{"id",       cxml::attr_type_hash}
		}
	});
	append_schema({
		"scroll_view",
		{"box", "page", "template", "group", "plane", "list_item", "plane_shadow"},
		{
			{"style",                     cxml::attr_type_idhashref},
			{"w_sbar_v",                  cxml::attr_type_hash},
			{"id",                        cxml::attr_type_hash},
			{"snap_anim_time",            cxml::attr_type_float},
			{"sbar_fadeout_time",         cxml::attr_type_float},
			{"w_sbar_h",                  cxml::attr_type_hash},
			{"auto_snap",                 cxml::attr_type_int},
			{"edit_auto_transition_mode", cxml::attr_type_int},
			{"snap_power",                cxml::attr_type_float}
		}
	});
	append_schema({
		"scrollbar",
		{"list_view", "browser_rich_text", "scroll_view", "rich_text", "template"},
		{
			{"style",       cxml::attr_type_idhashref},
			{"id",          cxml::attr_type_hash},
			{"scroll_type", cxml::attr_type_int}
		}
	});
	append_schema({
		"scrollbar_touch",
		{"box", "text_box", "list_view", "rich_text", "scroll_view"},
		{
			{"style",       cxml::attr_type_idhashref},
			{"id",          cxml::attr_type_hash},
			{"sound",       cxml::attr_type_idhashref},
			{"scroll_type", cxml::attr_type_int}
		}
	});
	append_schema({
		"slidebar",
		{"plane", "group"},
		{
			{"style",                 cxml::attr_type_idhashref},
			{"min_label_margin",      cxml::attr_type_float},
			{"min_label_mode",        cxml::attr_type_int},
			{"max_label_mode",        cxml::attr_type_int},
			{"w_max_label",           cxml::attr_type_hash},
			{"max_label_pos_mode",    cxml::attr_type_int},
			{"w_min_label",           cxml::attr_type_hash},
			{"touch_mode",            cxml::attr_type_int},
			{"slider_size",           cxml::attr_type_floatarray},
			{"max_label_margin",      cxml::attr_type_float},
			{"min_label_pos_mode",    cxml::attr_type_int},
			{"id",                    cxml::attr_type_hash},
			{"slider_label_margin",   cxml::attr_type_float},
			{"slider_label_mode",     cxml::attr_type_int},
			{"slider_label_pos_mode", cxml::attr_type_int},
			{"w_slider_label",        cxml::attr_type_hash}
		}
	});
	append_schema({
		"sliding_drawer",
		{"page"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"sound_banner_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_button",
		{"soundindextable"},
		{
			{"id",         cxml::attr_type_idhash},
			{"decide",     cxml::attr_type_idhashref},
			{"press",      cxml::attr_type_idhashref},
			{"move_out",   cxml::attr_type_idhashref},
			{"long_press", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_check_box",
		{"soundindextable"},
		{
			{"uncheck", cxml::attr_type_idhashref},
			{"check",   cxml::attr_type_idhashref},
			{"id",      cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_composite_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_corner_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_file_list",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_image_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_list_item",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_list_view",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_mapview",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_plane_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_radio_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_rich_text",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_scroll_view",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sound_scrollbar_touch",
		{"soundindextable"},
		{
			{"page_scroll",        cxml::attr_type_idhashref},
			{"drag_begin",         cxml::attr_type_idhashref},
			{"drag_end",           cxml::attr_type_idhashref},
			{"id",                 cxml::attr_type_idhash},
			{"page_scroll_repeat", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_text",
		{"soundindextable"},
		{
			{"id",          cxml::attr_type_idhash},
			{"link_tapped", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_text_box",
		{"soundindextable"},
		{
			{"tapped",      cxml::attr_type_idhashref},
			{"id",          cxml::attr_type_idhash},
			{"link_tapped", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_thumbnail_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_update_button",
		{"soundindextable"},
		{
			{"id",     cxml::attr_type_idhash},
			{"decide", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"sound_webview",
		{"soundindextable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"sounddata",
		{"sounddatatable"},
		{
			{"src",   cxml::attr_type_filename},
			{"rate",  cxml::attr_type_int},
			{"type",  cxml::attr_type_string},
			{"id",    cxml::attr_type_idhash},
			{"right", cxml::attr_type_filename},
			{"left",  cxml::attr_type_filename}
		}
	});
	append_schema({
		"sounddatatable",
		{"resource"},
		{
		}
	});
	append_schema({
		"soundindextable",
		{"resource"},
		{
		}
	});
	append_schema({
		"speech_balloon",
		{"plane", "scroll_view", "box", "template"},
		{
			{"style",   cxml::attr_type_idhashref},
			{"id",      cxml::attr_type_hash},
			{"texture", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"stringtable",
		{"resource"},
		{
		}
	});
	append_schema({
		"style_app_icon_simple",
		{"styletable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_banner_button",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"sound",    cxml::attr_type_idhashref},
			{"id",       cxml::attr_type_idhash},
			{"bg_obj",   cxml::attr_type_hash},
			{"glow_obj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_box",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"id",       cxml::attr_type_idhash},
			{"planeobj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_browser_rich_text",
		{"styletable"},
		{
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_busyindicator",
		{"styletable"},
		{
			{"ball_size",  cxml::attr_type_float},
			{"id",         cxml::attr_type_idhash},
			{"ball_color", cxml::attr_type_floatarray},
			{"color",      cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_button",
		{"styletable"},
		{
			{"color",           cxml::attr_type_floatarray},
			{"bg_obj",          cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"glow_obj",        cxml::attr_type_hash},
			{"right_margin",    cxml::attr_type_float},
			{"left_margin",     cxml::attr_type_float},
			{"label_obj",       cxml::attr_type_hash},
			{"adjust_min_size", cxml::attr_type_floatarray},
			{"sound",           cxml::attr_type_idhashref},
			{"bottom_margin",   cxml::attr_type_float},
			{"top_margin",      cxml::attr_type_float},
			{"highlight_obj",   cxml::attr_type_hash},
			{"focus_in_group",  cxml::attr_type_int},
			{"key_focus",       cxml::attr_type_int},
			{"direct_key",      cxml::attr_type_int},
			{"adjust_max_size", cxml::attr_type_floatarray},
			{"style_type",      cxml::attr_type_int}
		}
	});
	append_schema({
		"style_button_base",
		{"styletable"},
		{
			{"color", cxml::attr_type_floatarray},
			{"id",    cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_check_box",
		{"styletable"},
		{
			{"sound",       cxml::attr_type_idhashref},
			{"glow_obj",    cxml::attr_type_hash},
			{"color",       cxml::attr_type_floatarray},
			{"left_margin", cxml::attr_type_float},
			{"frame_num",   cxml::attr_type_int},
			{"image_obj",   cxml::attr_type_hash},
			{"id",          cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_color_change_button",
		{"styletable"},
		{
			{"color",  cxml::attr_type_floatarray},
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_color_shift_button",
		{"styletable"},
		{
			{"color", cxml::attr_type_floatarray},
			{"id",    cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_composite_button",
		{"styletable"},
		{
			{"color",       cxml::attr_type_floatarray},
			{"sound",       cxml::attr_type_idhashref},
			{"glow_obj_id", cxml::attr_type_int},
			{"id",          cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_composite_drawer",
		{"styletable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_corner_button",
		{"styletable"},
		{
			{"sound",          cxml::attr_type_idhashref},
			{"key_focus",      cxml::attr_type_int},
			{"corner_obj",     cxml::attr_type_hash},
			{"glow_obj",       cxml::attr_type_hash},
			{"highlight_obj",  cxml::attr_type_hash},
			{"focus_in_group", cxml::attr_type_int},
			{"direct_key",     cxml::attr_type_int},
			{"bg_obj",         cxml::attr_type_hash},
			{"layout_type",    cxml::attr_type_int},
			{"id",             cxml::attr_type_idhash},
			{"color",          cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_dialog",
		{"styletable"},
		{
			{"color", cxml::attr_type_floatarray},
			{"id",    cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_directbar",
		{"styletable"},
		{
			{"balloon_obj",   cxml::attr_type_hash},
			{"color",         cxml::attr_type_floatarray},
			{"launchbtn_obj", cxml::attr_type_hash},
			{"label_obj",     cxml::attr_type_hash},
			{"bg_obj",        cxml::attr_type_hash},
			{"id",            cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_drop_shadow_button",
		{"styletable"},
		{
			{"color",  cxml::attr_type_floatarray},
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_drop_shadow_plane",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"id",       cxml::attr_type_idhash},
			{"planeobj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_file_list",
		{"styletable"},
		{
			{"color",         cxml::attr_type_floatarray},
			{"bg_obj",        cxml::attr_type_hash},
			{"id",            cxml::attr_type_idhash},
			{"sbar_v_margin", cxml::attr_type_floatarray},
			{"sound",         cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"style_five_star_plane",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"id",       cxml::attr_type_idhash},
			{"planeobj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_group",
		{"styletable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_image_button",
		{"styletable"},
		{
			{"image_obj",       cxml::attr_type_hash},
			{"sound",           cxml::attr_type_idhashref},
			{"glow_obj",        cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"bottom_margin",   cxml::attr_type_float},
			{"layout_type_x",   cxml::attr_type_int},
			{"color",           cxml::attr_type_floatarray},
			{"right_margin",    cxml::attr_type_float},
			{"top_margin",      cxml::attr_type_float},
			{"left_margin",     cxml::attr_type_float},
			{"focus_in_group",  cxml::attr_type_int},
			{"label_obj",       cxml::attr_type_hash},
			{"bg_obj",          cxml::attr_type_hash},
			{"image_margin",    cxml::attr_type_float},
			{"highlight_obj",   cxml::attr_type_hash},
			{"image_back_obj",  cxml::attr_type_hash},
			{"layout_type_y",   cxml::attr_type_int},
			{"adjust_min_size", cxml::attr_type_floatarray},
			{"style_type",      cxml::attr_type_int},
			{"key_focus",       cxml::attr_type_int}
		}
	});
	append_schema({
		"style_image_slidebar",
		{"styletable"},
		{
			{"base_obj", cxml::attr_type_hash},
			{"id",       cxml::attr_type_idhash},
			{"bar_obj",  cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_list_edge",
		{"styletable"},
		{
			{"bottom_margin",    cxml::attr_type_float},
			{"top_margin",       cxml::attr_type_float},
			{"id",               cxml::attr_type_idhash},
			{"bottom_gradient",  cxml::attr_type_float},
			{"bottom_intercept", cxml::attr_type_float}
		}
	});
	append_schema({
		"style_list_item",
		{"styletable"},
		{
			{"color",  cxml::attr_type_floatarray},
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash},
			{"sound",  cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"style_list_view",
		{"styletable"},
		{
			{"color",                     cxml::attr_type_floatarray},
			{"bg_obj",                    cxml::attr_type_hash},
			{"id",                        cxml::attr_type_idhash},
			{"sound",                     cxml::attr_type_idhashref},
			{"cell_size_initial_default", cxml::attr_type_floatarray},
			{"sbar_v_margin",             cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_mapview",
		{"styletable"},
		{
			{"color",  cxml::attr_type_floatarray},
			{"sound",  cxml::attr_type_idhashref},
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_page",
		{"styletable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_plane",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"id",       cxml::attr_type_idhash},
			{"planeobj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_plane_button",
		{"styletable"},
		{
			{"key_focus",       cxml::attr_type_int},
			{"glow_obj",        cxml::attr_type_hash},
			{"color",           cxml::attr_type_floatarray},
			{"focus_in_group",  cxml::attr_type_int},
			{"direct_key",      cxml::attr_type_int},
			{"image_obj",       cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"sound",           cxml::attr_type_idhashref},
			{"bottom_margin",   cxml::attr_type_float},
			{"right_margin",    cxml::attr_type_float},
			{"top_margin",      cxml::attr_type_float},
			{"left_margin",     cxml::attr_type_float},
			{"adjust_min_size", cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_plane_shadow",
		{"styletable"},
		{
			{"shadow_obj", cxml::attr_type_hash},
			{"id",         cxml::attr_type_idhash},
			{"planeobj",   cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_progressbar",
		{"styletable"},
		{
			{"base_obj",        cxml::attr_type_hash},
			{"bar_fore_obj",    cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"shadow_margin",   cxml::attr_type_floatarray},
			{"shadow_offset",   cxml::attr_type_floatarray},
			{"glow_obj",        cxml::attr_type_hash},
			{"bar_shadow_obj",  cxml::attr_type_hash},
			{"bar_back_obj",    cxml::attr_type_hash},
			{"signal_obj",      cxml::attr_type_hash},
			{"base_shadow_obj", cxml::attr_type_hash},
			{"anim_func",       cxml::attr_type_int}
		}
	});
	append_schema({
		"style_progressbar_touch",
		{"styletable"},
		{
			{"base_obj",        cxml::attr_type_hash},
			{"slider_obj",      cxml::attr_type_hash},
			{"glow_obj",        cxml::attr_type_hash},
			{"bar_shadow_obj",  cxml::attr_type_hash},
			{"shadow_margin",   cxml::attr_type_floatarray},
			{"bar_fore_obj",    cxml::attr_type_hash},
			{"shadow_offset",   cxml::attr_type_floatarray},
			{"bar_back_obj",    cxml::attr_type_hash},
			{"signal_obj",      cxml::attr_type_hash},
			{"base_shadow_obj", cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"slider_glow_obj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_radio_box",
		{"styletable"},
		{
			{"id", cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_radio_button",
		{"styletable"},
		{
			{"sound",          cxml::attr_type_idhashref},
			{"bottom_margin",  cxml::attr_type_float},
			{"right_margin",   cxml::attr_type_float},
			{"color",          cxml::attr_type_floatarray},
			{"top_margin",     cxml::attr_type_float},
			{"left_margin",    cxml::attr_type_float},
			{"focus_in_group", cxml::attr_type_int},
			{"label_obj",      cxml::attr_type_hash},
			{"frame_num",      cxml::attr_type_int},
			{"image_obj",      cxml::attr_type_hash},
			{"id",             cxml::attr_type_idhash},
			{"glow_obj",       cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_rich_text",
		{"styletable"},
		{
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_scroll_view",
		{"styletable"},
		{
			{"color",         cxml::attr_type_floatarray},
			{"id",            cxml::attr_type_idhash},
			{"bg_obj",        cxml::attr_type_hash},
			{"sound",         cxml::attr_type_idhashref},
			{"sbar_v_margin", cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_scrollbar",
		{"styletable"},
		{
			{"min_size",     cxml::attr_type_float},
			{"base_obj",     cxml::attr_type_hash},
			{"slider_obj",   cxml::attr_type_hash},
			{"id",           cxml::attr_type_idhash},
			{"jet_tail_obj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_scrollbar2d",
		{"styletable"},
		{
			{"base_obj", cxml::attr_type_hash},
			{"id",       cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_scrollbar_touch",
		{"styletable"},
		{
			{"min_size",        cxml::attr_type_float},
			{"base_obj",        cxml::attr_type_hash},
			{"slider_obj",      cxml::attr_type_hash},
			{"slider_glow_obj", cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"sound",           cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"style_slidebar",
		{"styletable"},
		{
			{"base_obj",        cxml::attr_type_hash},
			{"slider_obj",      cxml::attr_type_hash},
			{"id",              cxml::attr_type_idhash},
			{"bar_obj",         cxml::attr_type_hash},
			{"slider_glow_obj", cxml::attr_type_hash},
			{"color",           cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_sliding_drawer",
		{"styletable"},
		{
			{"color", cxml::attr_type_floatarray},
			{"id",    cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_speech_balloon",
		{"styletable"},
		{
			{"shadow_obj", cxml::attr_type_hash},
			{"id",         cxml::attr_type_idhash},
			{"planeobj",   cxml::attr_type_hash},
			{"color",      cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_text",
		{"styletable"},
		{
			{"color",         cxml::attr_type_floatarray},
			{"textobj",       cxml::attr_type_hash},
			{"id",            cxml::attr_type_idhash},
			{"bottom_margin", cxml::attr_type_float},
			{"right_margin",  cxml::attr_type_float},
			{"top_margin",    cxml::attr_type_float},
			{"left_margin",   cxml::attr_type_float},
			{"planeobj",      cxml::attr_type_hash},
			{"sound",         cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"style_text_box",
		{"styletable"},
		{
			{"sound",         cxml::attr_type_idhashref},
			{"textobj",       cxml::attr_type_hash},
			{"right_margin",  cxml::attr_type_float},
			{"planeobj",      cxml::attr_type_hash},
			{"left_margin",   cxml::attr_type_float},
			{"id",            cxml::attr_type_idhash},
			{"bottom_margin", cxml::attr_type_float},
			{"top_margin",    cxml::attr_type_float},
			{"glowobj",       cxml::attr_type_hash},
			{"color",         cxml::attr_type_floatarray}
		}
	});
	append_schema({
		"style_thumbnail_button",
		{"styletable"},
		{
			{"color",    cxml::attr_type_floatarray},
			{"sound",    cxml::attr_type_idhashref},
			{"id",       cxml::attr_type_idhash},
			{"bg_obj",   cxml::attr_type_hash},
			{"glow_obj", cxml::attr_type_hash}
		}
	});
	append_schema({
		"style_update_button",
		{"styletable"},
		{
			{"image_obj", cxml::attr_type_hash},
			{"arrow_obj", cxml::attr_type_hash},
			{"glow_obj",  cxml::attr_type_hash},
			{"id",        cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_webview",
		{"styletable"},
		{
			{"color",  cxml::attr_type_floatarray},
			{"sound",  cxml::attr_type_idhashref},
			{"bg_obj", cxml::attr_type_hash},
			{"id",     cxml::attr_type_idhash}
		}
	});
	append_schema({
		"style_xm_list",
		{"styletable"},
		{
			{"color", cxml::attr_type_floatarray},
			{"id",    cxml::attr_type_idhash}
		}
	});
	append_schema({
		"styletable",
		{"resource"},
		{
		}
	});
	append_schema({
		"template",
		{"templatetable"},
		{
			{"id",        cxml::attr_type_idhash},
			{"fast_open", cxml::attr_type_int}
		}
	});
	append_schema({
		"template_ref",
		{"box", "plane", "group", "template", "page", "plane_button", "list_item", "button"},
		{
			{"id",       cxml::attr_type_hash},
			{"template", cxml::attr_type_idhashref}
		}
	});
	append_schema({
		"templatetable",
		{"resource"},
		{
		}
	});
	append_schema({
		"text",
		{"plane", "group", "rich_text", "drop_shadow_button", "box", "button", "list_item", "color_shift_button", "page", "template", "progressbar", "text", "progressbar_touch", "plane_button", "text_box", "list_view", "image_button", "scroll_view", "radio_button", "plane_shadow", "slidebar", "pagetable", "check_box"},
		{
			{"auto_scroll",                      cxml::attr_type_int},
			{"long_press_text_auto_scroll_mode", cxml::attr_type_int},
			{"style",                            cxml::attr_type_idhashref},
			{"id",                               cxml::attr_type_hash},
			{"label",                            cxml::attr_type_idhashref},
			{"selection_mode",                   cxml::attr_type_int},
			{"texture",                          cxml::attr_type_idhashref},
			{"scroll_view",                      cxml::attr_type_hash},
			{"auto_link_detect",                 cxml::attr_type_int},
			{"url_scheme",                       cxml::attr_type_int},
			{"label_alias",                      cxml::attr_type_idhashref},
			{"disable_auto_scroll",              cxml::attr_type_int},
			{"auto_scroll_target_friend",        cxml::attr_type_hash}
		}
	});
	append_schema({
		"text_box",
		{"plane", "text", "box", "group", "scroll_view", "page", "template", "plane_shadow", "list_item", "plane_button"},
		{
			{"style",                     cxml::attr_type_idhashref},
			{"id",                        cxml::attr_type_hash},
			{"label",                     cxml::attr_type_idhashref},
			{"selection_mode",            cxml::attr_type_int},
			{"edit_mode",                 cxml::attr_type_int},
			{"paste_mode",                cxml::attr_type_int},
			{"placeholder",               cxml::attr_type_idhashref},
			{"scroll_view",               cxml::attr_type_hash},
			{"edit_auto_transition_mode", cxml::attr_type_int},
			{"ime_type",                  cxml::attr_type_int},
			{"max_length",                cxml::attr_type_int},
			{"ime_option",                cxml::attr_type_int},
			{"sound",                     cxml::attr_type_idhashref},
			{"auto_scroll",               cxml::attr_type_int},
			{"texture",                   cxml::attr_type_idhashref},
			{"password_mode",             cxml::attr_type_int},
			{"v_scrollbar",               cxml::attr_type_hash},
			{"ime_supported_languages",   cxml::attr_type_int},
			{"ime_languages_forced",      cxml::attr_type_int}
		}
	});
	append_schema({
		"textobj",
		{"style_text", "style_button", "style_text_box", "style_radio_button", "style_image_button", "style_directbar", "style_composite_button", "style_composite_drawer"},
		{
			{"visible_size",       cxml::attr_type_floatarray},
			{"line_space",         cxml::attr_type_float},
			{"font_size",          cxml::attr_type_float},
			{"bold",               cxml::attr_type_int},
			{"family",             cxml::attr_type_int},
			{"align_y",            cxml::attr_type_int},
			{"align_x",            cxml::attr_type_int},
			{"oblique",            cxml::attr_type_int},
			{"back_color",         cxml::attr_type_floatarray},
			{"text_align",         cxml::attr_type_int},
			{"word_wrap",          cxml::attr_type_int},
			{"kinsoku",            cxml::attr_type_int},
			{"adjust_x",           cxml::attr_type_int},
			{"adjust_y",           cxml::attr_type_int},
			{"visible_pos",        cxml::attr_type_floatarray},
			{"ellipsis",           cxml::attr_type_int},
			{"underline",          cxml::attr_type_int},
			{"id",                 cxml::attr_type_hash},
			{"color",              cxml::attr_type_floatarray},
			{"size",               cxml::attr_type_floatarray},
			{"shadow_color",       cxml::attr_type_floatarray},
			{"underline_color",    cxml::attr_type_floatarray},
			{"emboss",             cxml::attr_type_int},
			{"strike_color",       cxml::attr_type_floatarray},
			{"strike",             cxml::attr_type_int},
			{"line_pitch",         cxml::attr_type_float},
			{"shadow",             cxml::attr_type_int},
			{"mask",               cxml::attr_type_int},
			{"font_color",         cxml::attr_type_floatarray},
			{"condense_x",         cxml::attr_type_int},
			{"enlarge_font_size",  cxml::attr_type_int},
			{"max_line_count",     cxml::attr_type_int},
			{"enlarge_line_pitch", cxml::attr_type_int},
			{"pos",                cxml::attr_type_floatarray},
			{"force_bold",         cxml::attr_type_int},
			{"deepen_color",       cxml::attr_type_int}
		}
	});
	append_schema({
		"texture",
		{"texturetable"},
		{
			{"src",                       cxml::attr_type_filename},
			{"origsize",                  cxml::attr_type_int},
			{"div_ratio_h",               cxml::attr_type_floatarray},
			{"compress",                  cxml::attr_type_string},
			{"margin_v",                  cxml::attr_type_intarray},
			{"div_mode",                  cxml::attr_type_string},
			{"margin_h",                  cxml::attr_type_intarray},
			{"div_ratio_v",               cxml::attr_type_floatarray},
			{"type",                      cxml::attr_type_string},
			{"id",                        cxml::attr_type_idhash},
			{"div_ratio_stretch",         cxml::attr_type_floatarray},
			{"ignore_make_surface_first", cxml::attr_type_string}
		}
	});
	append_schema({
		"texturetable",
		{"resource"},
		{
		}
	});
	append_schema({
		"thumbnail_button",
		{"template"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"update_button",
		{"group", "plane"},
		{
			{"sound", cxml::attr_type_idhashref},
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
	append_schema({
		"webview",
		{"plane"},
		{
			{"url_field",   cxml::attr_type_hash},
			{"title_field", cxml::attr_type_hash},
			{"forward_btn", cxml::attr_type_hash},
			{"progressbar", cxml::attr_type_hash},
			{"reload_btn",  cxml::attr_type_hash},
			{"home_url",    cxml::attr_type_string},
			{"back_btn",    cxml::attr_type_hash},
			{"id",          cxml::attr_type_hash}
		}
	});
	append_schema({
		"xm_list",
		{"template"},
		{
			{"style", cxml::attr_type_idhashref},
			{"id",    cxml::attr_type_hash}
		}
	});
}

int rco::compiler::rco_fileProvider_default(tinyxml2::XMLElement *tag, const char *path, cxml::stack& fileimage, void *argp){

	int res;

	if(strcmp(tag->Name(), "locale") == 0){

		rcs::compiler compiler;

		res = compiler.CompileXml(path);
		if(res < 0){
			return res;
		}

		res = compiler.GetCxmlData(fileimage);
		if(res < 0){
			return res;
		}
	}else{
		res = fileimage.append_file_data(path, NULL);
		if(res < 0){
			return res;
		}
	}

	const tinyxml2::XMLAttribute *attr = tag->FindAttribute("compress");

	if(attr != NULL && strcmp(attr->Value(), "on") == 0){
		int size = fileimage.GetSize();
		if(size < 0) {
			printf("File size must fit in int (%u ~ %u). (%s)\n", 0, ~0, attr->Value());
			return -1;
		}

		char _origsize[0x40];
		snprintf(_origsize, sizeof(_origsize), "%d", size);
		tag->SetAttribute("origsize", _origsize);

		res = fileimage.Compress();
		if(res < 0){
			return res;
		}
	}

	return 0;
}

int rco::compiler::Compile(const char *xml_path){
	return CompileXml(xml_path, rco_fileProvider_default);
}
